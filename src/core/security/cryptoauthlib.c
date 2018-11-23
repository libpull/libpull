#include <libpull/security/digest.h>
#include <libpull/security/ecc.h>
#include <string.h>
#include <stdio.h>

#if WITH_CRYPTOAUTHLIB

#include <cryptoauthlib.h>
#include <crypto/atca_crypto_sw_sha2.h>

#if WITH_CRYPTOAUTHLIB_HW

pull_error digest_init(digest_ctx* ctx) {
    if (atcab_hw_sha2_256_init(&ctx->sha256_cryptoauthlib_hw.ctx) != ATCA_SUCCESS) {
        return SHA256_INIT_ERROR;
    }
    return PULL_SUCCESS;
}

pull_error digest_update(digest_ctx* ctx, void* data, size_t data_size) {
    if (atcab_hw_sha2_256_update(&ctx->sha256_cryptoauthlib_hw.ctx, (const uint8_t *) data, data_size) != ATCA_SUCCESS) {
        return SHA256_UPDATE_ERROR;
    }
    return PULL_SUCCESS;
}

void* digest_finalize(digest_ctx* ctx) {
    if (atcab_hw_sha2_256_finish(&ctx->sha256_cryptoauthlib_hw.ctx, (uint8_t*) &ctx->sha256_cryptoauthlib_hw.result) != ATCA_SUCCESS) {
        return NULL;
    }
    return &ctx->sha256_cryptoauthlib_hw.result;
}

uint16_t get_digest_size() {
    return 32;
}

#elif WITH_CRYPTOAUTHLIB_SW

pull_error digest_init(digest_ctx* ctx) {
    if (atcac_sw_sha2_256_init(&ctx->sha256_cryptoauthlib.ctx) != ATCA_SUCCESS) {
        return SHA256_INIT_ERROR;
    }
    return PULL_SUCCESS;
}

pull_error digest_update(digest_ctx* ctx, void* data, size_t data_size) {
    if (atcac_sw_sha2_256_update(&ctx->sha256_cryptoauthlib.ctx, (const uint8_t *) data, data_size) != ATCA_SUCCESS) {
        return SHA256_UPDATE_ERROR;
    }
    return PULL_SUCCESS;
}

void* digest_finalize(digest_ctx* ctx) {
    if (atcac_sw_sha2_256_finish(&ctx->sha256_cryptoauthlib.ctx, (uint8_t*) &ctx->sha256_cryptoauthlib.result) != ATCA_SUCCESS) {
        return NULL;
    }
    return &ctx->sha256_cryptoauthlib.result;
}

uint16_t get_digest_size() {
    return 32;
}

#endif /* WITH_CRYPTOAUTHLIB_** */

/* ECC */

pull_error ecc_verify(const uint8_t* x, const uint8_t* y, const uint8_t* r, const uint8_t* s,
        const void* data, uint16_t data_len) {
    uint8_t pub_key[64];
    uint8_t signature[64];
    bool is_verified;
    if (data_len != 32) {
        return VERIFICATION_FAILED_ERROR;
    }
    memcpy(pub_key, x, 32);
    memcpy(pub_key+32, y, 32);
    memcpy(signature, r, 32);
    memcpy(signature+32, s, 32);
    if (atcab_verify_extern(data, (const uint8_t*)signature, (const uint8_t*)pub_key, &is_verified)
            != ATCA_SUCCESS) {
        return VERIFICATION_FAILED_ERROR;
    }
    return is_verified? PULL_SUCCESS: VERIFICATION_FAILED_ERROR;
}

pull_error ecc_sign(const uint8_t* private_key, uint8_t *signature,
                     const void *data, uint16_t data_len) {
    return NOT_IMPLEMENTED_ERROR;
}


#endif /* WITH_CRYPTOAUTHLIB */

