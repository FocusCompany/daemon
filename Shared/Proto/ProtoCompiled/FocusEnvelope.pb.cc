// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: FocusEnvelope.proto

#include "FocusEnvelope.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/port.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// This is a temporary google only hack
#ifdef GOOGLE_PROTOBUF_ENFORCE_UNIQUENESS
#include "third_party/protobuf/version.h"
#endif
// @@protoc_insertion_point(includes)
class FocusEnveloppeDefaultTypeInternal {
 public:
  ::google::protobuf::internal::ExplicitlyConstructed<FocusEnveloppe>
      _instance;
} _FocusEnveloppe_default_instance_;
namespace protobuf_FocusEnvelope_2eproto {
void InitDefaultsFocusEnveloppeImpl() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

#ifdef GOOGLE_PROTOBUF_ENFORCE_UNIQUENESS
  ::google::protobuf::internal::InitProtobufDefaultsForceUnique();
#else
  ::google::protobuf::internal::InitProtobufDefaults();
#endif  // GOOGLE_PROTOBUF_ENFORCE_UNIQUENESS
  protobuf_google_2fprotobuf_2fany_2eproto::InitDefaultsAny();
  {
    void* ptr = &::_FocusEnveloppe_default_instance_;
    new (ptr) ::FocusEnveloppe();
    ::google::protobuf::internal::OnShutdownDestroyMessage(ptr);
  }
  ::FocusEnveloppe::InitAsDefaultInstance();
}

void InitDefaultsFocusEnveloppe() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &InitDefaultsFocusEnveloppeImpl);
}

::google::protobuf::Metadata file_level_metadata[1];

const ::google::protobuf::uint32 TableStruct::offsets[] GOOGLE_PROTOBUF_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::FocusEnveloppe, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::FocusEnveloppe, clientid_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::FocusEnveloppe, payloadtype_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::FocusEnveloppe, payload_),
};
static const ::google::protobuf::internal::MigrationSchema schemas[] GOOGLE_PROTOBUF_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, sizeof(::FocusEnveloppe)},
};

static ::google::protobuf::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::google::protobuf::Message*>(&::_FocusEnveloppe_default_instance_),
};

void protobuf_AssignDescriptors() {
  AddDescriptors();
  ::google::protobuf::MessageFactory* factory = NULL;
  AssignDescriptors(
      "FocusEnvelope.proto", schemas, file_default_instances, TableStruct::offsets, factory,
      file_level_metadata, NULL, NULL);
}

void protobuf_AssignDescriptorsOnce() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &protobuf_AssignDescriptors);
}

void protobuf_RegisterTypes(const ::std::string&) GOOGLE_PROTOBUF_ATTRIBUTE_COLD;
void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::internal::RegisterAllTypes(file_level_metadata, 1);
}

void AddDescriptorsImpl() {
  InitDefaults();
  static const char descriptor[] GOOGLE_PROTOBUF_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
      "\n\023FocusEnvelope.proto\032\031google/protobuf/a"
      "ny.proto\"^\n\016FocusEnveloppe\022\020\n\010ClientID\030\001"
      " \001(\t\022\023\n\013PayloadType\030\002 \001(\t\022%\n\007Payload\030\003 \001"
      "(\0132\024.google.protobuf.Anyb\006proto3"
  };
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
      descriptor, 152);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "FocusEnvelope.proto", &protobuf_RegisterTypes);
  ::protobuf_google_2fprotobuf_2fany_2eproto::AddDescriptors();
}

void AddDescriptors() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &AddDescriptorsImpl);
}
// Force AddDescriptors() to be called at dynamic initialization time.
struct StaticDescriptorInitializer {
  StaticDescriptorInitializer() {
    AddDescriptors();
  }
} static_descriptor_initializer;
}  // namespace protobuf_FocusEnvelope_2eproto

// ===================================================================

void FocusEnveloppe::InitAsDefaultInstance() {
  ::_FocusEnveloppe_default_instance_._instance.get_mutable()->payload_ = const_cast< ::google::protobuf::Any*>(
      ::google::protobuf::Any::internal_default_instance());
}
void FocusEnveloppe::clear_payload() {
  if (GetArenaNoVirtual() == NULL && payload_ != NULL) {
    delete payload_;
  }
  payload_ = NULL;
}
#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int FocusEnveloppe::kClientIDFieldNumber;
const int FocusEnveloppe::kPayloadTypeFieldNumber;
const int FocusEnveloppe::kPayloadFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

FocusEnveloppe::FocusEnveloppe()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  if (GOOGLE_PREDICT_TRUE(this != internal_default_instance())) {
    ::protobuf_FocusEnvelope_2eproto::InitDefaultsFocusEnveloppe();
  }
  SharedCtor();
  // @@protoc_insertion_point(constructor:FocusEnveloppe)
}
FocusEnveloppe::FocusEnveloppe(const FocusEnveloppe& from)
  : ::google::protobuf::Message(),
      _internal_metadata_(NULL),
      _cached_size_(0) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  clientid_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  if (from.clientid().size() > 0) {
    clientid_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.clientid_);
  }
  payloadtype_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  if (from.payloadtype().size() > 0) {
    payloadtype_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.payloadtype_);
  }
  if (from.has_payload()) {
    payload_ = new ::google::protobuf::Any(*from.payload_);
  } else {
    payload_ = NULL;
  }
  // @@protoc_insertion_point(copy_constructor:FocusEnveloppe)
}

void FocusEnveloppe::SharedCtor() {
  clientid_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  payloadtype_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  payload_ = NULL;
  _cached_size_ = 0;
}

FocusEnveloppe::~FocusEnveloppe() {
  // @@protoc_insertion_point(destructor:FocusEnveloppe)
  SharedDtor();
}

void FocusEnveloppe::SharedDtor() {
  clientid_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  payloadtype_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  if (this != internal_default_instance()) delete payload_;
}

void FocusEnveloppe::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* FocusEnveloppe::descriptor() {
  ::protobuf_FocusEnvelope_2eproto::protobuf_AssignDescriptorsOnce();
  return ::protobuf_FocusEnvelope_2eproto::file_level_metadata[kIndexInFileMessages].descriptor;
}

const FocusEnveloppe& FocusEnveloppe::default_instance() {
  ::protobuf_FocusEnvelope_2eproto::InitDefaultsFocusEnveloppe();
  return *internal_default_instance();
}

FocusEnveloppe* FocusEnveloppe::New(::google::protobuf::Arena* arena) const {
  FocusEnveloppe* n = new FocusEnveloppe;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void FocusEnveloppe::Clear() {
// @@protoc_insertion_point(message_clear_start:FocusEnveloppe)
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  clientid_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  payloadtype_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  if (GetArenaNoVirtual() == NULL && payload_ != NULL) {
    delete payload_;
  }
  payload_ = NULL;
  _internal_metadata_.Clear();
}

bool FocusEnveloppe::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:FocusEnveloppe)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // string ClientID = 1;
      case 1: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(10u /* 10 & 0xFF */)) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_clientid()));
          DO_(::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
            this->clientid().data(), static_cast<int>(this->clientid().length()),
            ::google::protobuf::internal::WireFormatLite::PARSE,
            "FocusEnveloppe.ClientID"));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // string PayloadType = 2;
      case 2: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(18u /* 18 & 0xFF */)) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_payloadtype()));
          DO_(::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
            this->payloadtype().data(), static_cast<int>(this->payloadtype().length()),
            ::google::protobuf::internal::WireFormatLite::PARSE,
            "FocusEnveloppe.PayloadType"));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // .google.protobuf.Any Payload = 3;
      case 3: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(26u /* 26 & 0xFF */)) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessage(
               input, mutable_payload()));
        } else {
          goto handle_unusual;
        }
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, _internal_metadata_.mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:FocusEnveloppe)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:FocusEnveloppe)
  return false;
#undef DO_
}

void FocusEnveloppe::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:FocusEnveloppe)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // string ClientID = 1;
  if (this->clientid().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->clientid().data(), static_cast<int>(this->clientid().length()),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "FocusEnveloppe.ClientID");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      1, this->clientid(), output);
  }

  // string PayloadType = 2;
  if (this->payloadtype().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->payloadtype().data(), static_cast<int>(this->payloadtype().length()),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "FocusEnveloppe.PayloadType");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      2, this->payloadtype(), output);
  }

  // .google.protobuf.Any Payload = 3;
  if (this->has_payload()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      3, *this->payload_, output);
  }

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()), output);
  }
  // @@protoc_insertion_point(serialize_end:FocusEnveloppe)
}

::google::protobuf::uint8* FocusEnveloppe::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  (void)deterministic; // Unused
  // @@protoc_insertion_point(serialize_to_array_start:FocusEnveloppe)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // string ClientID = 1;
  if (this->clientid().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->clientid().data(), static_cast<int>(this->clientid().length()),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "FocusEnveloppe.ClientID");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        1, this->clientid(), target);
  }

  // string PayloadType = 2;
  if (this->payloadtype().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->payloadtype().data(), static_cast<int>(this->payloadtype().length()),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "FocusEnveloppe.PayloadType");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        2, this->payloadtype(), target);
  }

  // .google.protobuf.Any Payload = 3;
  if (this->has_payload()) {
    target = ::google::protobuf::internal::WireFormatLite::
      InternalWriteMessageToArray(
        3, *this->payload_, deterministic, target);
  }

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:FocusEnveloppe)
  return target;
}

size_t FocusEnveloppe::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:FocusEnveloppe)
  size_t total_size = 0;

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()));
  }
  // string ClientID = 1;
  if (this->clientid().size() > 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->clientid());
  }

  // string PayloadType = 2;
  if (this->payloadtype().size() > 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->payloadtype());
  }

  // .google.protobuf.Any Payload = 3;
  if (this->has_payload()) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::MessageSize(
        *this->payload_);
  }

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = cached_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void FocusEnveloppe::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:FocusEnveloppe)
  GOOGLE_DCHECK_NE(&from, this);
  const FocusEnveloppe* source =
      ::google::protobuf::internal::DynamicCastToGenerated<const FocusEnveloppe>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:FocusEnveloppe)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:FocusEnveloppe)
    MergeFrom(*source);
  }
}

void FocusEnveloppe::MergeFrom(const FocusEnveloppe& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:FocusEnveloppe)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.clientid().size() > 0) {

    clientid_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.clientid_);
  }
  if (from.payloadtype().size() > 0) {

    payloadtype_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.payloadtype_);
  }
  if (from.has_payload()) {
    mutable_payload()->::google::protobuf::Any::MergeFrom(from.payload());
  }
}

void FocusEnveloppe::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:FocusEnveloppe)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void FocusEnveloppe::CopyFrom(const FocusEnveloppe& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:FocusEnveloppe)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool FocusEnveloppe::IsInitialized() const {
  return true;
}

void FocusEnveloppe::Swap(FocusEnveloppe* other) {
  if (other == this) return;
  InternalSwap(other);
}
void FocusEnveloppe::InternalSwap(FocusEnveloppe* other) {
  using std::swap;
  clientid_.Swap(&other->clientid_);
  payloadtype_.Swap(&other->payloadtype_);
  swap(payload_, other->payload_);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata FocusEnveloppe::GetMetadata() const {
  protobuf_FocusEnvelope_2eproto::protobuf_AssignDescriptorsOnce();
  return ::protobuf_FocusEnvelope_2eproto::file_level_metadata[kIndexInFileMessages];
}


// @@protoc_insertion_point(namespace_scope)

// @@protoc_insertion_point(global_scope)
