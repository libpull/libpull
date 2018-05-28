#include <libpull/network/receiver.h>
#include <libpull/network/async_interface.h>
#include <libpull/memory/memory_objects.h>
#include <libpull/memory/memory_interface.h>
#include <libpull/common.h>
#include <string.h>

#define MAX_RECEIVER_ERRORS 10

static void handler(pull_error txp_err, const char* data, int len, void* more) {
    receiver_ctx* ctx = (receiver_ctx*) more;
    if (txp_err) {
        log_error(txp_err, "Network failure\n");
        ctx->err = NETWORK_ERROR; 
        break_loop(ctx->txp);
        return;
    }
    if (len <= 0) {
        log_error(NETWORK_ERROR, "The received lenght (%d) is invalid\n", len);
        ctx->err = NETWORK_ERROR; 
        break_loop(ctx->txp);
        return;
    }
    if (memory_write(ctx->obj, (const uint8_t*) data, len, ctx->received) != len) {
        log_error(MEMORY_WRITE_ERROR, "Failure writing the received data\n");
        ctx->err = MEMORY_WRITE_ERROR;
        break_loop(ctx->txp);
        return;
    }
    if (!ctx->manifest_received) {
        log_debug("Manifest still not received\n");
        int16_t missing = sizeof(manifest_t)-ctx->received;
        if (missing <= 0) {
            log_debug("Manifest received\n");
            print_manifest(&ctx->mt);
            if (validate_identity(ctx->identity, get_identity(&ctx->mt)) != PULL_SUCCESS) { 
                log_debug("Received invalid identity\n");
                ctx->err = INVALID_IDENTITY_ERROR;
                break_loop(ctx->txp);
                return;
            }
            ctx->expected = get_size(&ctx->mt)+get_offset(&ctx->mt);
            // TODO find a way to check if the firmware to receive is
            // bigger than the object size
            // XXX the value returned by get_size is an unsigned and it does not
            // make sense to check for <= 0; TODO fix it
            if (get_size(&ctx->mt) <= 0 /* ||ctx->mt.vendor.size > MAX_FIRMWARE_SIZE-sizeof(manifest_t)*/) {
                log_debug("Received an invalid size %d, aborting\n", (int) ctx->mt.vendor.size);
                ctx->err = INVALID_SIZE_ERROR;
                break_loop(ctx->txp);
                return;
            }
            ctx->manifest_received = 1;
        } else {
            uint8_t* mt_ptr = (uint8_t*) &ctx->mt;
            memcpy(mt_ptr+ctx->received, data, ctx->received+len<=sizeof(manifest_t)? len: missing);
        }
    }
    ctx->received+=len;
    if (ctx->manifest_received) {
        log_info("Received %u bytes. Expected %u bytes\r", ctx->received, ctx->expected);
        if (ctx->received == ctx->expected) {
            ctx->firmware_received = 1;
            ctx->err = PULL_SUCCESS;
            break_loop(ctx->txp);
        } else if (ctx->received > ctx->expected) {
            ctx->err = INVALID_SIZE_ERROR;
            log_error(INVALID_SIZE_ERROR, "Error receiving the firmware\n");
            break_loop(ctx->txp);
            return;
        }
    }
}

pull_error receiver_open(receiver_ctx* ctx, txp_ctx* txp, identity_t identity,
        const char* resource, mem_object_t* obj) {
    memset(ctx, 0, sizeof(receiver_ctx));
    ctx->txp = txp;
    ctx->err = PULL_SUCCESS;
    ctx->obj = obj;
    ctx->resource = resource;
    ctx->identity = identity;
    ctx->obj = obj;
    ctx->firmware_received = 0;
    return PULL_SUCCESS;
}

pull_error receiver_chunk(receiver_ctx* ctx) {
    pull_error err = txp_on_data(ctx->txp, handler, ctx);
    if (err) {
        log_error(err, "Failure setting receiver callback\n");
        return RECEIVER_CHUNK_ERROR;
    }
    ctx->start_offset = ctx->received;
    switch(ctx->err) {
        // Recoverable errors
        case MEMORY_WRITE_ERROR:
        case NETWORK_ERROR:
            if (++ctx->num_err >= MAX_RECEIVER_ERRORS) {
                return ctx->err;
            }
            ctx->err = PULL_SUCCESS;
            break;
            // Not recoverable error. The upgrade process should start again
        case INVALID_SIZE_ERROR:
            return ctx->err;
        default: /* ignore all the other cases */ break;
    }
    ctx->msg.msg_version = MESSAGE_VERSION;
    ctx->msg.offset = ctx->start_offset;
    ctx->msg.udid = ctx->identity.udid;
    ctx->msg.random = ctx->identity.random;
    err = txp_request(ctx->txp, GET_BLOCKWISE2, ctx->resource, (const char*) &(ctx->msg), sizeof(receiver_msg_t));
    if (err) {
        log_error(err, "Failure setting receiver request\n");
        return RECEIVER_CHUNK_ERROR;
    }
    return PULL_SUCCESS;
}

pull_error receiver_close(receiver_ctx* ctx) {
    /* Do nothing */
    return PULL_SUCCESS;
}
