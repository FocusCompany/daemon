// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: FocusEvent.proto

#ifndef PROTOBUF_FocusEvent_2eproto__INCLUDED
#define PROTOBUF_FocusEvent_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3005000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3005000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
#include <google/protobuf/any.pb.h>
#include <google/protobuf/timestamp.pb.h>
// @@protoc_insertion_point(includes)

namespace protobuf_FocusEvent_2eproto {
// Internal implementation detail -- do not use these members.
struct TableStruct {
  static const ::google::protobuf::internal::ParseTableField entries[];
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[];
  static const ::google::protobuf::internal::ParseTable schema[1];
  static const ::google::protobuf::internal::FieldMetadata field_metadata[];
  static const ::google::protobuf::internal::SerializationTable serialization_table[];
  static const ::google::protobuf::uint32 offsets[];
};
void AddDescriptors();
void InitDefaultsEventImpl();
void InitDefaultsEvent();
inline void InitDefaults() {
  InitDefaultsEvent();
}
}  // namespace protobuf_FocusEvent_2eproto
namespace Focus {
class Event;
class EventDefaultTypeInternal;
extern EventDefaultTypeInternal _Event_default_instance_;
}  // namespace Focus
namespace Focus {

// ===================================================================

class Event : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:Focus.Event) */ {
 public:
  Event();
  virtual ~Event();

  Event(const Event& from);

  inline Event& operator=(const Event& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  Event(Event&& from) noexcept
    : Event() {
    *this = ::std::move(from);
  }

  inline Event& operator=(Event&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const Event& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const Event* internal_default_instance() {
    return reinterpret_cast<const Event*>(
               &_Event_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    0;

  void Swap(Event* other);
  friend void swap(Event& a, Event& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline Event* New() const PROTOBUF_FINAL { return New(NULL); }

  Event* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const Event& from);
  void MergeFrom(const Event& from);
  void Clear() PROTOBUF_FINAL;
  bool IsInitialized() const PROTOBUF_FINAL;

  size_t ByteSizeLong() const PROTOBUF_FINAL;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) PROTOBUF_FINAL;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const PROTOBUF_FINAL;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const PROTOBUF_FINAL;
  int GetCachedSize() const PROTOBUF_FINAL { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const PROTOBUF_FINAL;
  void InternalSwap(Event* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const PROTOBUF_FINAL;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // string payloadType = 2;
  void clear_payloadtype();
  static const int kPayloadTypeFieldNumber = 2;
  const ::std::string& payloadtype() const;
  void set_payloadtype(const ::std::string& value);
  #if LANG_CXX11
  void set_payloadtype(::std::string&& value);
  #endif
  void set_payloadtype(const char* value);
  void set_payloadtype(const char* value, size_t size);
  ::std::string* mutable_payloadtype();
  ::std::string* release_payloadtype();
  void set_allocated_payloadtype(::std::string* payloadtype);

  // .google.protobuf.Timestamp timestamp = 1;
  bool has_timestamp() const;
  void clear_timestamp();
  static const int kTimestampFieldNumber = 1;
  const ::google::protobuf::Timestamp& timestamp() const;
  ::google::protobuf::Timestamp* release_timestamp();
  ::google::protobuf::Timestamp* mutable_timestamp();
  void set_allocated_timestamp(::google::protobuf::Timestamp* timestamp);

  // .google.protobuf.Any payload = 3;
  bool has_payload() const;
  void clear_payload();
  static const int kPayloadFieldNumber = 3;
  const ::google::protobuf::Any& payload() const;
  ::google::protobuf::Any* release_payload();
  ::google::protobuf::Any* mutable_payload();
  void set_allocated_payload(::google::protobuf::Any* payload);

  // @@protoc_insertion_point(class_scope:Focus.Event)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr payloadtype_;
  ::google::protobuf::Timestamp* timestamp_;
  ::google::protobuf::Any* payload_;
  mutable int _cached_size_;
  friend struct ::protobuf_FocusEvent_2eproto::TableStruct;
  friend void ::protobuf_FocusEvent_2eproto::InitDefaultsEventImpl();
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// Event

// .google.protobuf.Timestamp timestamp = 1;
inline bool Event::has_timestamp() const {
  return this != internal_default_instance() && timestamp_ != NULL;
}
inline const ::google::protobuf::Timestamp& Event::timestamp() const {
  const ::google::protobuf::Timestamp* p = timestamp_;
  // @@protoc_insertion_point(field_get:Focus.Event.timestamp)
  return p != NULL ? *p : *reinterpret_cast<const ::google::protobuf::Timestamp*>(
      &::google::protobuf::_Timestamp_default_instance_);
}
inline ::google::protobuf::Timestamp* Event::release_timestamp() {
  // @@protoc_insertion_point(field_release:Focus.Event.timestamp)
  
  ::google::protobuf::Timestamp* temp = timestamp_;
  timestamp_ = NULL;
  return temp;
}
inline ::google::protobuf::Timestamp* Event::mutable_timestamp() {
  
  if (timestamp_ == NULL) {
    timestamp_ = new ::google::protobuf::Timestamp;
  }
  // @@protoc_insertion_point(field_mutable:Focus.Event.timestamp)
  return timestamp_;
}
inline void Event::set_allocated_timestamp(::google::protobuf::Timestamp* timestamp) {
  ::google::protobuf::Arena* message_arena = GetArenaNoVirtual();
  if (message_arena == NULL) {
    delete reinterpret_cast< ::google::protobuf::MessageLite*>(timestamp_);
  }
  if (timestamp) {
    ::google::protobuf::Arena* submessage_arena =
      reinterpret_cast< ::google::protobuf::MessageLite*>(timestamp)->GetArena();
    if (message_arena != submessage_arena) {
      timestamp = ::google::protobuf::internal::GetOwnedMessage(
          message_arena, timestamp, submessage_arena);
    }
    
  } else {
    
  }
  timestamp_ = timestamp;
  // @@protoc_insertion_point(field_set_allocated:Focus.Event.timestamp)
}

// string payloadType = 2;
inline void Event::clear_payloadtype() {
  payloadtype_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& Event::payloadtype() const {
  // @@protoc_insertion_point(field_get:Focus.Event.payloadType)
  return payloadtype_.GetNoArena();
}
inline void Event::set_payloadtype(const ::std::string& value) {
  
  payloadtype_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:Focus.Event.payloadType)
}
#if LANG_CXX11
inline void Event::set_payloadtype(::std::string&& value) {
  
  payloadtype_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:Focus.Event.payloadType)
}
#endif
inline void Event::set_payloadtype(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  payloadtype_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:Focus.Event.payloadType)
}
inline void Event::set_payloadtype(const char* value, size_t size) {
  
  payloadtype_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:Focus.Event.payloadType)
}
inline ::std::string* Event::mutable_payloadtype() {
  
  // @@protoc_insertion_point(field_mutable:Focus.Event.payloadType)
  return payloadtype_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* Event::release_payloadtype() {
  // @@protoc_insertion_point(field_release:Focus.Event.payloadType)
  
  return payloadtype_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Event::set_allocated_payloadtype(::std::string* payloadtype) {
  if (payloadtype != NULL) {
    
  } else {
    
  }
  payloadtype_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), payloadtype);
  // @@protoc_insertion_point(field_set_allocated:Focus.Event.payloadType)
}

// .google.protobuf.Any payload = 3;
inline bool Event::has_payload() const {
  return this != internal_default_instance() && payload_ != NULL;
}
inline const ::google::protobuf::Any& Event::payload() const {
  const ::google::protobuf::Any* p = payload_;
  // @@protoc_insertion_point(field_get:Focus.Event.payload)
  return p != NULL ? *p : *reinterpret_cast<const ::google::protobuf::Any*>(
      &::google::protobuf::_Any_default_instance_);
}
inline ::google::protobuf::Any* Event::release_payload() {
  // @@protoc_insertion_point(field_release:Focus.Event.payload)
  
  ::google::protobuf::Any* temp = payload_;
  payload_ = NULL;
  return temp;
}
inline ::google::protobuf::Any* Event::mutable_payload() {
  
  if (payload_ == NULL) {
    payload_ = new ::google::protobuf::Any;
  }
  // @@protoc_insertion_point(field_mutable:Focus.Event.payload)
  return payload_;
}
inline void Event::set_allocated_payload(::google::protobuf::Any* payload) {
  ::google::protobuf::Arena* message_arena = GetArenaNoVirtual();
  if (message_arena == NULL) {
    delete reinterpret_cast< ::google::protobuf::MessageLite*>(payload_);
  }
  if (payload) {
    ::google::protobuf::Arena* submessage_arena = NULL;
    if (message_arena != submessage_arena) {
      payload = ::google::protobuf::internal::GetOwnedMessage(
          message_arena, payload, submessage_arena);
    }
    
  } else {
    
  }
  payload_ = payload;
  // @@protoc_insertion_point(field_set_allocated:Focus.Event.payload)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace Focus

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_FocusEvent_2eproto__INCLUDED
