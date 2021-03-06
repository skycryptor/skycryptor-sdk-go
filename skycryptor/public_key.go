package skycryptor

/*
#include "cryptomagic_c.h"
#include "stdlib.h"
 */
import "C"
import "unsafe"

// PublicKey object, which is Go implementation of extended C/C++ library interface
type PublicKey struct {
  Key
}

// Cleaning up C/C++ allocations for private key object
func (pk *PublicKey) Clean() {
  C.cryptomagic_public_key_free(pk.pointer)
}

// Making encapsulation and getting Capsule with symmetric key
func (pk *PublicKey) Encapsulate() (capsule *Capsule, symmetric_key []byte) {
  var c_buffer *C.char
  c_buffer_len := C.int(0)
  capsule = &Capsule{cm: pk.cm}
  capsule.pointer = C.cryptomagic_encapsulate(pk.cm.pointer, pk.pointer, &c_buffer, &c_buffer_len)
  symmetric_key = C.GoBytes(unsafe.Pointer(c_buffer), c_buffer_len)
  C.free(unsafe.Pointer(c_buffer))
  return capsule, symmetric_key
}

// Encoding public key to bytes
func (pk *PublicKey) ToBytes() (pkData []byte) {
  var c_buffer *C.char
  c_buffer_len := C.int(0)
  C.cryptomagic_public_key_to_bytes(pk.pointer, &c_buffer, &c_buffer_len)
  pkData = C.GoBytes(unsafe.Pointer(c_buffer), c_buffer_len)
  C.free(unsafe.Pointer(c_buffer))
  return pkData
}

// Getting public key CryptoMagic object from given byte data
func PublicKeyFromBytes(cm *CryptoMagic, pkData []byte) *PublicKey {
  pk := &PublicKey{}
  pk.cm = cm
  pk.pointer = C.cryptomagic_public_key_from_bytes(cm.pointer, (*C.char)(unsafe.Pointer(&pkData[0])), C.int(len(pkData)))
  return pk
}
