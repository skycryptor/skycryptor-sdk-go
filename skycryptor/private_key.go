package skycryptor

/*
#include "cryptomagic_c.h"
#include "stdlib.h"
 */
import "C"
import "unsafe"

// PrivateKey object, which is Go implementation of extended C/C++ library interface
type PrivateKey struct {
  Key
}

// Cleaning up C/C++ allocations for private key object
func (sk *PrivateKey) Clean() {
  C.cryptomagic_private_key_free(sk.pointer);
}

// Getting public key from our private key
func (sk *PrivateKey) GetPublicKey() *PublicKey {
  pk := &PublicKey{Key: Key{cm: sk.cm}}
  pk.pointer = C.cryptomagic_get_public_key(sk.pointer)
  return pk
}

// Converting our private key to Bytes
func (sk *PrivateKey) ToBytes() []byte {
  var c_buffer *C.char
  c_buffer_len := C.int(0)
  C.cryptomagic_private_key_to_bytes(sk.pointer, &c_buffer,&c_buffer_len)
  retBuf := C.GoBytes(unsafe.Pointer(c_buffer), c_buffer_len)
  C.free(unsafe.Pointer(c_buffer))
  return retBuf
}

// Decapsulating given capsule and getting back symmetric key
func (sk *PrivateKey) Decapsulate(capsule *Capsule) (symmetricKey []byte) {
  var c_buffer *C.char
  c_buffer_len := C.int(0)
  C.cryptomagic_decapsulate_original(sk.cm.pointer, capsule.pointer, sk.pointer, &c_buffer, &c_buffer_len)
  retBuf := C.GoBytes(unsafe.Pointer(c_buffer), c_buffer_len)
  C.free(unsafe.Pointer(c_buffer))
  return retBuf
}

// Getting private key CryptoMagic object from given byte data
func PrivateKeyFromBytes(cm *CryptoMagic, skData []byte) *PrivateKey {
  sk := &PrivateKey{}
  sk.cm = cm
  sk.pointer = C.cryptomagic_private_key_from_bytes(cm.pointer, (*C.char)(unsafe.Pointer(&skData[0])), C.int(len(skData)))
  return sk
}