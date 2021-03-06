#include <libpull/security.h>
#include <string.h>

#if WITH_TINYCRYPT

#include <tinycrypt/sha256.h>
#include <tinycrypt/ecc_dsa.h>

/* SHA 256 */

pull_error digest_init(digest_ctx* ctx) {
    if (ctx == NULL || tc_sha256_init(&ctx->sha256_tinycrypt.ctx) != 1) {
        return DIGEST_INIT_ERROR;
    }
    return PULL_SUCCESS;
}

pull_error digest_update(digest_ctx* ctx, void* data, size_t data_size) {
    if (ctx == NULL || data == NULL || tc_sha256_update(&ctx->sha256_tinycrypt.ctx, (const uint8_t *) data, (size_t) data_size) != 1) {
        return DIGEST_UPDATE_ERROR;
    }
    return PULL_SUCCESS;
}

void* digest_finalize(digest_ctx* ctx) {
    if (ctx == NULL || tc_sha256_final((uint8_t*) &ctx->sha256_tinycrypt.result, 
                &ctx->sha256_tinycrypt.ctx) != 1) {
        return NULL;
    }
    return &ctx->sha256_tinycrypt.result;
}

uint16_t get_digest_size() {
    return 32;
}

/* ECC */

pull_error ecc_verify(const uint8_t* x, const uint8_t* y, const uint8_t* r, const uint8_t* s,
        const void* data, uint16_t data_len) {
    uint8_t pub_key[64];
    uint8_t signature[64];
    memcpy(pub_key, x, 32);
    memcpy(pub_key+32, y, 32);
    memcpy(signature, r, 32);
    memcpy(signature+32, s, 32);
    if (uECC_verify(pub_key, (uint8_t*) data, (size_t) data_len, signature, uECC_secp256r1()) != 1) {
        return VERIFICATION_FAILED_ERROR;
    }
    return PULL_SUCCESS;
}

pull_error ecc_sign(const uint8_t* private_key, uint8_t *signature, 
                    const void *data, uint16_t data_len) {
     if (uECC_sign(private_key, data, data_len, signature, uECC_secp256r1()) != 1) {
        return SIGN_FAILED_ERROR;
     }
     return PULL_SUCCESS;
}

uint8_t get_curve_size() {
    return 32; 
}

/* AES */

pull_error aes128_init(aes128_ctx_t* ctx, safestore_t* sf) {
    // This is safe up to AES 128
    // https://github.com/01org/tinycrypt/blob/master/lib/include/tinycrypt/aes.h#L104

    if (!tc_aes128_set_decrypt_key(&ctx->aes128_tinycrypt.s, sf->aes_key)) {
        return GENERIC_ERROR; 
    }
    return PULL_SUCCESS;
}

pull_error aes128_decypt(aes128_ctx_t* ctx, uint8_t* out, const uint8_t* in) {
    if (!tc_aes_decrypt(out, in, &ctx->aes128_tinycrypt.s)) {
        return GENERIC_ERROR;
    }
    return PULL_SUCCESS;
}

#endif /* WITH_TINYCRYPT */
