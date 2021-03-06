//
// Created by Tigran on 7/6/18.
//

#ifndef CRYPTOMAIC_CRYPTOMAGIC_H
#define CRYPTOMAIC_CRYPTOMAGIC_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief Making any memory allocations here needed to operate this library from C interface
 */
void cryptomagic_init();

/**
 * \brief For interfacing with C and other languages we need higher level functions and non class based pointers
 * This function initiates CryptoMagic class object and turning it as a void * pointer to keep it inside other
 * languages contexts, where they can reference to that class over our C API, just providing that void * memory pointer
 * @return CryptoMagic pointer converted to (void *)
 */
void * cryptomagic_new();

/**
 * \brief Cleaning up all allocations and main CryptoMagic object allocation
 * NOTE: this will crash if badly if we will pass wrong pointer from other languages, BUT that's on owr own risk!
 * @param cm
 */
void cryptomagic_clear(void *cm_ptr);

/**
 * \brief Generating private key from given CryptoMagic pointer
 * @param cm_ptr
 * @return raw pointer to private key
 */
void * cryptomagic_generate_private_key(void *cm_ptr);

/**
 * \brief Clearing private key from memory
 * @param private_key_ptr
 */
void cryptomagic_private_key_free(void *private_key_ptr);

/**
 * \brief Getting public key from given private key
 * @param private_key_ptr
 * @return raw pointer to public key object
 */
void * cryptomagic_get_public_key(void *private_key_ptr);

/**
 * \brief Getting raw bytes from given private key
 * @param private_key_ptr
 * @param[out] buffer
 * @param[out] length
 */
void cryptomagic_private_key_to_bytes(void *private_key_ptr, char **buffer, int *length);

/**
 * \brief Getting raw bytes from given public key
 * @param public_key_ptr
 * @param[out] buffer
 * @param[out] length
 */
void cryptomagic_public_key_to_bytes(void *public_key_ptr, char **buffer, int *length);

/**
 * \brief Allocating and getting private key from given bytes array
 * @param cm_ptr
 * @param buffer
 * @param length
 * @return Allocated private key pointer
 */
void * cryptomagic_private_key_from_bytes(void * cm_ptr, const char *buffer, int length);

/**
 * \brief Allocating and getting public key from given bytes array
 * @param cm_ptr
 * @param buffer
 * @param length
 * @return Allocated private key pointer
 */
void * cryptomagic_public_key_from_bytes(void * cm_ptr, char *buffer, int length);

/**
 * \brief Cleaning up public key object from memory
 * @param public_key_ptr
 * @return
 */
void cryptomagic_public_key_free(void *public_key_ptr);

/**
 * \brief Handling encapsulation process and returning both Capsule raw pointer and symmetric key buffer
 * @param cm_ptr main cryptomagic object raw pointer to perform action
 * @param public_key_ptr
 * @package[out] symmetric_key_out
 * @package[out] symmetric_key_len
 * @return raw pointer to capsule object
 */
void * cryptomagic_encapsulate(void * cm_ptr, void *public_key_ptr, char **symmetric_key_out, int *symmetric_key_len);

/**
 * \brief Cleaning capsule from memory
 * @param capsule_ptr
 */
void cryptomagic_capsule_free(void *capsule_ptr);

/**
 * \brief Decapsulating given capsule with given private key and returning symmetric byte buffer
 * @param cm_ptr main cryptomagic object raw pointer to perform action
 * @param private_key_ptr
 * @param[out] symmetric_key_out
 * @param[out] symmetric_key_len
 */
void cryptomagic_decapsulate(void * cm_ptr, void *capsule_ptr, void * private_key_ptr, char **symmetric_key_out, int *symmetric_key_len);

/**
 * \brief Converting given capsule to byte array
 * @param capsule
 * @param[out] buffer
 * @param[out] length
 */
void cryptomagic_capsule_to_bytes(void *capsule, char **buffer, int *length);

/**
 * \brief Allocating and returning capsule from given byte array
 * @param cm_ptr
 * @param buffer
 * @param length
 * @return
 */
void * cryptomagic_capsule_from_bytes(void * cm_ptr, char *buffer, int length);

/**
 * \brief Getting re-encryption key A->B using PrivateKey A and PublicKey B
 * @param cm_ptr main cryptomagic object raw pointer to perform action
 * @param skA_ptr
 * @param pkB_ptr
 * @return
 */
void * cryptomagic_get_re_encryption_key(void * cm_ptr, void *skA_ptr, void *pkB_ptr);

/**
 * \brief Getting re-encryption key form bytes
 * @param cm_ptr
 * @param buffer
 * @param length
 * @return
 */
void * cryptomagic_get_re_encryption_from_bytes(void * cm_ptr, char *buffer, int length);

/**
 * \brief getting encoded bytes from reencryption key
 * @param[out] buffer
 * @param[out] length
 * @param rkk
 * @return
 */
void cryptomagic_re_encryption_to_bytes(void * rkk_ptr, char **buffer, int *length);

/**
 * \brief Cleaning up re-encryption key from memory
 * @param rkk_ptr
 */
void cryptomagic_re_encryption_key_free(void *rkk_ptr);

/**
 * \brief Getting re-encryption capsule using Original capsule and PublicKey B
 * @param cm_ptr main cryptomagic object raw pointer to perform action
 * @param capsule_ptr
 * @param rkAB_ptr
 * @return
 */
void * cryptomagic_get_re_encryption_capsule(void * cm_ptr, void * capsule_ptr, void *rkAB_ptr);

#ifdef __cplusplus
}
#endif

#endif //CRYPTOMAIC_CRYPTOMAGIC_H
