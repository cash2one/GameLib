// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: accsrv.proto

#ifndef PROTOBUF_accsrv_2eproto__INCLUDED
#define PROTOBUF_accsrv_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2005000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2005000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/unknown_field_set.h>
#include "options.pb.h"
// @@protoc_insertion_point(includes)

namespace Net {
namespace accsrv {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_accsrv_2eproto();
void protobuf_AssignDesc_accsrv_2eproto();
void protobuf_ShutdownFile_accsrv_2eproto();

class CSLogin;
class SCLoginResult;

// ===================================================================

class CSLogin : public ::google::protobuf::Message {
 public:
  CSLogin();
  virtual ~CSLogin();

  CSLogin(const CSLogin& from);

  inline CSLogin& operator=(const CSLogin& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const CSLogin& default_instance();

  void Swap(CSLogin* other);

  // implements Message ----------------------------------------------

  CSLogin* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const CSLogin& from);
  void MergeFrom(const CSLogin& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required string name = 1;
  inline bool has_name() const;
  inline void clear_name();
  static const int kNameFieldNumber = 1;
  inline const ::std::string& name() const;
  inline void set_name(const ::std::string& value);
  inline void set_name(const char* value);
  inline void set_name(const char* value, size_t size);
  inline ::std::string* mutable_name();
  inline ::std::string* release_name();
  inline void set_allocated_name(::std::string* name);

  // required string pswd = 2;
  inline bool has_pswd() const;
  inline void clear_pswd();
  static const int kPswdFieldNumber = 2;
  inline const ::std::string& pswd() const;
  inline void set_pswd(const ::std::string& value);
  inline void set_pswd(const char* value);
  inline void set_pswd(const char* value, size_t size);
  inline ::std::string* mutable_pswd();
  inline ::std::string* release_pswd();
  inline void set_allocated_pswd(::std::string* pswd);

  // @@protoc_insertion_point(class_scope:Net.accsrv.CSLogin)
 private:
  inline void set_has_name();
  inline void clear_has_name();
  inline void set_has_pswd();
  inline void clear_has_pswd();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::std::string* name_;
  ::std::string* pswd_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];

  friend void  protobuf_AddDesc_accsrv_2eproto();
  friend void protobuf_AssignDesc_accsrv_2eproto();
  friend void protobuf_ShutdownFile_accsrv_2eproto();

  void InitAsDefaultInstance();
  static CSLogin* default_instance_;
};
// -------------------------------------------------------------------

class SCLoginResult : public ::google::protobuf::Message {
 public:
  SCLoginResult();
  virtual ~SCLoginResult();

  SCLoginResult(const SCLoginResult& from);

  inline SCLoginResult& operator=(const SCLoginResult& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const SCLoginResult& default_instance();

  void Swap(SCLoginResult* other);

  // implements Message ----------------------------------------------

  SCLoginResult* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const SCLoginResult& from);
  void MergeFrom(const SCLoginResult& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required int32 result = 1;
  inline bool has_result() const;
  inline void clear_result();
  static const int kResultFieldNumber = 1;
  inline ::google::protobuf::int32 result() const;
  inline void set_result(::google::protobuf::int32 value);

  // optional string error = 2;
  inline bool has_error() const;
  inline void clear_error();
  static const int kErrorFieldNumber = 2;
  inline const ::std::string& error() const;
  inline void set_error(const ::std::string& value);
  inline void set_error(const char* value);
  inline void set_error(const char* value, size_t size);
  inline ::std::string* mutable_error();
  inline ::std::string* release_error();
  inline void set_allocated_error(::std::string* error);

  // @@protoc_insertion_point(class_scope:Net.accsrv.SCLoginResult)
 private:
  inline void set_has_result();
  inline void clear_has_result();
  inline void set_has_error();
  inline void clear_has_error();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::std::string* error_;
  ::google::protobuf::int32 result_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];

  friend void  protobuf_AddDesc_accsrv_2eproto();
  friend void protobuf_AssignDesc_accsrv_2eproto();
  friend void protobuf_ShutdownFile_accsrv_2eproto();

  void InitAsDefaultInstance();
  static SCLoginResult* default_instance_;
};
// ===================================================================


// ===================================================================

// CSLogin

// required string name = 1;
inline bool CSLogin::has_name() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void CSLogin::set_has_name() {
  _has_bits_[0] |= 0x00000001u;
}
inline void CSLogin::clear_has_name() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void CSLogin::clear_name() {
  if (name_ != &::google::protobuf::internal::kEmptyString) {
    name_->clear();
  }
  clear_has_name();
}
inline const ::std::string& CSLogin::name() const {
  return *name_;
}
inline void CSLogin::set_name(const ::std::string& value) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  name_->assign(value);
}
inline void CSLogin::set_name(const char* value) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  name_->assign(value);
}
inline void CSLogin::set_name(const char* value, size_t size) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  name_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* CSLogin::mutable_name() {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  return name_;
}
inline ::std::string* CSLogin::release_name() {
  clear_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = name_;
    name_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void CSLogin::set_allocated_name(::std::string* name) {
  if (name_ != &::google::protobuf::internal::kEmptyString) {
    delete name_;
  }
  if (name) {
    set_has_name();
    name_ = name;
  } else {
    clear_has_name();
    name_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// required string pswd = 2;
inline bool CSLogin::has_pswd() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void CSLogin::set_has_pswd() {
  _has_bits_[0] |= 0x00000002u;
}
inline void CSLogin::clear_has_pswd() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void CSLogin::clear_pswd() {
  if (pswd_ != &::google::protobuf::internal::kEmptyString) {
    pswd_->clear();
  }
  clear_has_pswd();
}
inline const ::std::string& CSLogin::pswd() const {
  return *pswd_;
}
inline void CSLogin::set_pswd(const ::std::string& value) {
  set_has_pswd();
  if (pswd_ == &::google::protobuf::internal::kEmptyString) {
    pswd_ = new ::std::string;
  }
  pswd_->assign(value);
}
inline void CSLogin::set_pswd(const char* value) {
  set_has_pswd();
  if (pswd_ == &::google::protobuf::internal::kEmptyString) {
    pswd_ = new ::std::string;
  }
  pswd_->assign(value);
}
inline void CSLogin::set_pswd(const char* value, size_t size) {
  set_has_pswd();
  if (pswd_ == &::google::protobuf::internal::kEmptyString) {
    pswd_ = new ::std::string;
  }
  pswd_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* CSLogin::mutable_pswd() {
  set_has_pswd();
  if (pswd_ == &::google::protobuf::internal::kEmptyString) {
    pswd_ = new ::std::string;
  }
  return pswd_;
}
inline ::std::string* CSLogin::release_pswd() {
  clear_has_pswd();
  if (pswd_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = pswd_;
    pswd_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void CSLogin::set_allocated_pswd(::std::string* pswd) {
  if (pswd_ != &::google::protobuf::internal::kEmptyString) {
    delete pswd_;
  }
  if (pswd) {
    set_has_pswd();
    pswd_ = pswd;
  } else {
    clear_has_pswd();
    pswd_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// -------------------------------------------------------------------

// SCLoginResult

// required int32 result = 1;
inline bool SCLoginResult::has_result() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void SCLoginResult::set_has_result() {
  _has_bits_[0] |= 0x00000001u;
}
inline void SCLoginResult::clear_has_result() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void SCLoginResult::clear_result() {
  result_ = 0;
  clear_has_result();
}
inline ::google::protobuf::int32 SCLoginResult::result() const {
  return result_;
}
inline void SCLoginResult::set_result(::google::protobuf::int32 value) {
  set_has_result();
  result_ = value;
}

// optional string error = 2;
inline bool SCLoginResult::has_error() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void SCLoginResult::set_has_error() {
  _has_bits_[0] |= 0x00000002u;
}
inline void SCLoginResult::clear_has_error() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void SCLoginResult::clear_error() {
  if (error_ != &::google::protobuf::internal::kEmptyString) {
    error_->clear();
  }
  clear_has_error();
}
inline const ::std::string& SCLoginResult::error() const {
  return *error_;
}
inline void SCLoginResult::set_error(const ::std::string& value) {
  set_has_error();
  if (error_ == &::google::protobuf::internal::kEmptyString) {
    error_ = new ::std::string;
  }
  error_->assign(value);
}
inline void SCLoginResult::set_error(const char* value) {
  set_has_error();
  if (error_ == &::google::protobuf::internal::kEmptyString) {
    error_ = new ::std::string;
  }
  error_->assign(value);
}
inline void SCLoginResult::set_error(const char* value, size_t size) {
  set_has_error();
  if (error_ == &::google::protobuf::internal::kEmptyString) {
    error_ = new ::std::string;
  }
  error_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* SCLoginResult::mutable_error() {
  set_has_error();
  if (error_ == &::google::protobuf::internal::kEmptyString) {
    error_ = new ::std::string;
  }
  return error_;
}
inline ::std::string* SCLoginResult::release_error() {
  clear_has_error();
  if (error_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = error_;
    error_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void SCLoginResult::set_allocated_error(::std::string* error) {
  if (error_ != &::google::protobuf::internal::kEmptyString) {
    delete error_;
  }
  if (error) {
    set_has_error();
    error_ = error;
  } else {
    clear_has_error();
    error_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace accsrv
}  // namespace Net

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_accsrv_2eproto__INCLUDED
