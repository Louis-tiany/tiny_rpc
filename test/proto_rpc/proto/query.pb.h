// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: query.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_query_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_query_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3014000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3014000 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_query_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_query_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxiliaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[3]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const ::PROTOBUF_NAMESPACE_ID::uint32 offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_query_2eproto;
namespace rpc {
class Answer;
class AnswerDefaultTypeInternal;
extern AnswerDefaultTypeInternal _Answer_default_instance_;
class Empty;
class EmptyDefaultTypeInternal;
extern EmptyDefaultTypeInternal _Empty_default_instance_;
class Query;
class QueryDefaultTypeInternal;
extern QueryDefaultTypeInternal _Query_default_instance_;
}  // namespace rpc
PROTOBUF_NAMESPACE_OPEN
template<> ::rpc::Answer* Arena::CreateMaybeMessage<::rpc::Answer>(Arena*);
template<> ::rpc::Empty* Arena::CreateMaybeMessage<::rpc::Empty>(Arena*);
template<> ::rpc::Query* Arena::CreateMaybeMessage<::rpc::Query>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace rpc {

// ===================================================================

class Query PROTOBUF_FINAL :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:rpc.Query) */ {
 public:
  inline Query() : Query(nullptr) {}
  virtual ~Query();

  Query(const Query& from);
  Query(Query&& from) noexcept
    : Query() {
    *this = ::std::move(from);
  }

  inline Query& operator=(const Query& from) {
    CopyFrom(from);
    return *this;
  }
  inline Query& operator=(Query&& from) noexcept {
    if (GetArena() == from.GetArena()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const Query& default_instance();

  static inline const Query* internal_default_instance() {
    return reinterpret_cast<const Query*>(
               &_Query_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(Query& a, Query& b) {
    a.Swap(&b);
  }
  inline void Swap(Query* other) {
    if (other == this) return;
    if (GetArena() == other->GetArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(Query* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline Query* New() const final {
    return CreateMaybeMessage<Query>(nullptr);
  }

  Query* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<Query>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const Query& from);
  void MergeFrom(const Query& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(Query* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "rpc.Query";
  }
  protected:
  explicit Query(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_query_2eproto);
    return ::descriptor_table_query_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kQuestionFieldNumber = 3,
    kQuestionerFieldNumber = 2,
    kIdFieldNumber = 1,
  };
  // repeated string question = 3;
  int question_size() const;
  private:
  int _internal_question_size() const;
  public:
  void clear_question();
  const std::string& question(int index) const;
  std::string* mutable_question(int index);
  void set_question(int index, const std::string& value);
  void set_question(int index, std::string&& value);
  void set_question(int index, const char* value);
  void set_question(int index, const char* value, size_t size);
  std::string* add_question();
  void add_question(const std::string& value);
  void add_question(std::string&& value);
  void add_question(const char* value);
  void add_question(const char* value, size_t size);
  const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField<std::string>& question() const;
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField<std::string>* mutable_question();
  private:
  const std::string& _internal_question(int index) const;
  std::string* _internal_add_question();
  public:

  // string questioner = 2;
  void clear_questioner();
  const std::string& questioner() const;
  void set_questioner(const std::string& value);
  void set_questioner(std::string&& value);
  void set_questioner(const char* value);
  void set_questioner(const char* value, size_t size);
  std::string* mutable_questioner();
  std::string* release_questioner();
  void set_allocated_questioner(std::string* questioner);
  private:
  const std::string& _internal_questioner() const;
  void _internal_set_questioner(const std::string& value);
  std::string* _internal_mutable_questioner();
  public:

  // int64 id = 1;
  void clear_id();
  ::PROTOBUF_NAMESPACE_ID::int64 id() const;
  void set_id(::PROTOBUF_NAMESPACE_ID::int64 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::int64 _internal_id() const;
  void _internal_set_id(::PROTOBUF_NAMESPACE_ID::int64 value);
  public:

  // @@protoc_insertion_point(class_scope:rpc.Query)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField<std::string> question_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr questioner_;
  ::PROTOBUF_NAMESPACE_ID::int64 id_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_query_2eproto;
};
// -------------------------------------------------------------------

class Answer PROTOBUF_FINAL :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:rpc.Answer) */ {
 public:
  inline Answer() : Answer(nullptr) {}
  virtual ~Answer();

  Answer(const Answer& from);
  Answer(Answer&& from) noexcept
    : Answer() {
    *this = ::std::move(from);
  }

  inline Answer& operator=(const Answer& from) {
    CopyFrom(from);
    return *this;
  }
  inline Answer& operator=(Answer&& from) noexcept {
    if (GetArena() == from.GetArena()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const Answer& default_instance();

  static inline const Answer* internal_default_instance() {
    return reinterpret_cast<const Answer*>(
               &_Answer_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  friend void swap(Answer& a, Answer& b) {
    a.Swap(&b);
  }
  inline void Swap(Answer* other) {
    if (other == this) return;
    if (GetArena() == other->GetArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(Answer* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline Answer* New() const final {
    return CreateMaybeMessage<Answer>(nullptr);
  }

  Answer* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<Answer>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const Answer& from);
  void MergeFrom(const Answer& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(Answer* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "rpc.Answer";
  }
  protected:
  explicit Answer(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_query_2eproto);
    return ::descriptor_table_query_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kSolutionFieldNumber = 4,
    kQuestionerFieldNumber = 2,
    kAnswererFieldNumber = 3,
    kIdFieldNumber = 1,
  };
  // repeated string solution = 4;
  int solution_size() const;
  private:
  int _internal_solution_size() const;
  public:
  void clear_solution();
  const std::string& solution(int index) const;
  std::string* mutable_solution(int index);
  void set_solution(int index, const std::string& value);
  void set_solution(int index, std::string&& value);
  void set_solution(int index, const char* value);
  void set_solution(int index, const char* value, size_t size);
  std::string* add_solution();
  void add_solution(const std::string& value);
  void add_solution(std::string&& value);
  void add_solution(const char* value);
  void add_solution(const char* value, size_t size);
  const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField<std::string>& solution() const;
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField<std::string>* mutable_solution();
  private:
  const std::string& _internal_solution(int index) const;
  std::string* _internal_add_solution();
  public:

  // string questioner = 2;
  void clear_questioner();
  const std::string& questioner() const;
  void set_questioner(const std::string& value);
  void set_questioner(std::string&& value);
  void set_questioner(const char* value);
  void set_questioner(const char* value, size_t size);
  std::string* mutable_questioner();
  std::string* release_questioner();
  void set_allocated_questioner(std::string* questioner);
  private:
  const std::string& _internal_questioner() const;
  void _internal_set_questioner(const std::string& value);
  std::string* _internal_mutable_questioner();
  public:

  // string answerer = 3;
  void clear_answerer();
  const std::string& answerer() const;
  void set_answerer(const std::string& value);
  void set_answerer(std::string&& value);
  void set_answerer(const char* value);
  void set_answerer(const char* value, size_t size);
  std::string* mutable_answerer();
  std::string* release_answerer();
  void set_allocated_answerer(std::string* answerer);
  private:
  const std::string& _internal_answerer() const;
  void _internal_set_answerer(const std::string& value);
  std::string* _internal_mutable_answerer();
  public:

  // int64 id = 1;
  void clear_id();
  ::PROTOBUF_NAMESPACE_ID::int64 id() const;
  void set_id(::PROTOBUF_NAMESPACE_ID::int64 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::int64 _internal_id() const;
  void _internal_set_id(::PROTOBUF_NAMESPACE_ID::int64 value);
  public:

  // @@protoc_insertion_point(class_scope:rpc.Answer)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField<std::string> solution_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr questioner_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr answerer_;
  ::PROTOBUF_NAMESPACE_ID::int64 id_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_query_2eproto;
};
// -------------------------------------------------------------------

class Empty PROTOBUF_FINAL :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:rpc.Empty) */ {
 public:
  inline Empty() : Empty(nullptr) {}
  virtual ~Empty();

  Empty(const Empty& from);
  Empty(Empty&& from) noexcept
    : Empty() {
    *this = ::std::move(from);
  }

  inline Empty& operator=(const Empty& from) {
    CopyFrom(from);
    return *this;
  }
  inline Empty& operator=(Empty&& from) noexcept {
    if (GetArena() == from.GetArena()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const Empty& default_instance();

  static inline const Empty* internal_default_instance() {
    return reinterpret_cast<const Empty*>(
               &_Empty_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    2;

  friend void swap(Empty& a, Empty& b) {
    a.Swap(&b);
  }
  inline void Swap(Empty* other) {
    if (other == this) return;
    if (GetArena() == other->GetArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(Empty* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline Empty* New() const final {
    return CreateMaybeMessage<Empty>(nullptr);
  }

  Empty* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<Empty>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const Empty& from);
  void MergeFrom(const Empty& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(Empty* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "rpc.Empty";
  }
  protected:
  explicit Empty(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_query_2eproto);
    return ::descriptor_table_query_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kIdFieldNumber = 2,
  };
  // int32 id = 2;
  bool has_id() const;
  private:
  bool _internal_has_id() const;
  public:
  void clear_id();
  ::PROTOBUF_NAMESPACE_ID::int32 id() const;
  void set_id(::PROTOBUF_NAMESPACE_ID::int32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::int32 _internal_id() const;
  void _internal_set_id(::PROTOBUF_NAMESPACE_ID::int32 value);
  public:

  // @@protoc_insertion_point(class_scope:rpc.Empty)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::internal::HasBits<1> _has_bits_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  ::PROTOBUF_NAMESPACE_ID::int32 id_;
  friend struct ::TableStruct_query_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// Query

// int64 id = 1;
inline void Query::clear_id() {
  id_ = PROTOBUF_LONGLONG(0);
}
inline ::PROTOBUF_NAMESPACE_ID::int64 Query::_internal_id() const {
  return id_;
}
inline ::PROTOBUF_NAMESPACE_ID::int64 Query::id() const {
  // @@protoc_insertion_point(field_get:rpc.Query.id)
  return _internal_id();
}
inline void Query::_internal_set_id(::PROTOBUF_NAMESPACE_ID::int64 value) {
  
  id_ = value;
}
inline void Query::set_id(::PROTOBUF_NAMESPACE_ID::int64 value) {
  _internal_set_id(value);
  // @@protoc_insertion_point(field_set:rpc.Query.id)
}

// string questioner = 2;
inline void Query::clear_questioner() {
  questioner_.ClearToEmpty();
}
inline const std::string& Query::questioner() const {
  // @@protoc_insertion_point(field_get:rpc.Query.questioner)
  return _internal_questioner();
}
inline void Query::set_questioner(const std::string& value) {
  _internal_set_questioner(value);
  // @@protoc_insertion_point(field_set:rpc.Query.questioner)
}
inline std::string* Query::mutable_questioner() {
  // @@protoc_insertion_point(field_mutable:rpc.Query.questioner)
  return _internal_mutable_questioner();
}
inline const std::string& Query::_internal_questioner() const {
  return questioner_.Get();
}
inline void Query::_internal_set_questioner(const std::string& value) {
  
  questioner_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, value, GetArena());
}
inline void Query::set_questioner(std::string&& value) {
  
  questioner_.Set(
    ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, ::std::move(value), GetArena());
  // @@protoc_insertion_point(field_set_rvalue:rpc.Query.questioner)
}
inline void Query::set_questioner(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  questioner_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, ::std::string(value), GetArena());
  // @@protoc_insertion_point(field_set_char:rpc.Query.questioner)
}
inline void Query::set_questioner(const char* value,
    size_t size) {
  
  questioner_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, ::std::string(
      reinterpret_cast<const char*>(value), size), GetArena());
  // @@protoc_insertion_point(field_set_pointer:rpc.Query.questioner)
}
inline std::string* Query::_internal_mutable_questioner() {
  
  return questioner_.Mutable(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, GetArena());
}
inline std::string* Query::release_questioner() {
  // @@protoc_insertion_point(field_release:rpc.Query.questioner)
  return questioner_.Release(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
}
inline void Query::set_allocated_questioner(std::string* questioner) {
  if (questioner != nullptr) {
    
  } else {
    
  }
  questioner_.SetAllocated(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), questioner,
      GetArena());
  // @@protoc_insertion_point(field_set_allocated:rpc.Query.questioner)
}

// repeated string question = 3;
inline int Query::_internal_question_size() const {
  return question_.size();
}
inline int Query::question_size() const {
  return _internal_question_size();
}
inline void Query::clear_question() {
  question_.Clear();
}
inline std::string* Query::add_question() {
  // @@protoc_insertion_point(field_add_mutable:rpc.Query.question)
  return _internal_add_question();
}
inline const std::string& Query::_internal_question(int index) const {
  return question_.Get(index);
}
inline const std::string& Query::question(int index) const {
  // @@protoc_insertion_point(field_get:rpc.Query.question)
  return _internal_question(index);
}
inline std::string* Query::mutable_question(int index) {
  // @@protoc_insertion_point(field_mutable:rpc.Query.question)
  return question_.Mutable(index);
}
inline void Query::set_question(int index, const std::string& value) {
  // @@protoc_insertion_point(field_set:rpc.Query.question)
  question_.Mutable(index)->assign(value);
}
inline void Query::set_question(int index, std::string&& value) {
  // @@protoc_insertion_point(field_set:rpc.Query.question)
  question_.Mutable(index)->assign(std::move(value));
}
inline void Query::set_question(int index, const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  question_.Mutable(index)->assign(value);
  // @@protoc_insertion_point(field_set_char:rpc.Query.question)
}
inline void Query::set_question(int index, const char* value, size_t size) {
  question_.Mutable(index)->assign(
    reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:rpc.Query.question)
}
inline std::string* Query::_internal_add_question() {
  return question_.Add();
}
inline void Query::add_question(const std::string& value) {
  question_.Add()->assign(value);
  // @@protoc_insertion_point(field_add:rpc.Query.question)
}
inline void Query::add_question(std::string&& value) {
  question_.Add(std::move(value));
  // @@protoc_insertion_point(field_add:rpc.Query.question)
}
inline void Query::add_question(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  question_.Add()->assign(value);
  // @@protoc_insertion_point(field_add_char:rpc.Query.question)
}
inline void Query::add_question(const char* value, size_t size) {
  question_.Add()->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_add_pointer:rpc.Query.question)
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField<std::string>&
Query::question() const {
  // @@protoc_insertion_point(field_list:rpc.Query.question)
  return question_;
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField<std::string>*
Query::mutable_question() {
  // @@protoc_insertion_point(field_mutable_list:rpc.Query.question)
  return &question_;
}

// -------------------------------------------------------------------

// Answer

// int64 id = 1;
inline void Answer::clear_id() {
  id_ = PROTOBUF_LONGLONG(0);
}
inline ::PROTOBUF_NAMESPACE_ID::int64 Answer::_internal_id() const {
  return id_;
}
inline ::PROTOBUF_NAMESPACE_ID::int64 Answer::id() const {
  // @@protoc_insertion_point(field_get:rpc.Answer.id)
  return _internal_id();
}
inline void Answer::_internal_set_id(::PROTOBUF_NAMESPACE_ID::int64 value) {
  
  id_ = value;
}
inline void Answer::set_id(::PROTOBUF_NAMESPACE_ID::int64 value) {
  _internal_set_id(value);
  // @@protoc_insertion_point(field_set:rpc.Answer.id)
}

// string questioner = 2;
inline void Answer::clear_questioner() {
  questioner_.ClearToEmpty();
}
inline const std::string& Answer::questioner() const {
  // @@protoc_insertion_point(field_get:rpc.Answer.questioner)
  return _internal_questioner();
}
inline void Answer::set_questioner(const std::string& value) {
  _internal_set_questioner(value);
  // @@protoc_insertion_point(field_set:rpc.Answer.questioner)
}
inline std::string* Answer::mutable_questioner() {
  // @@protoc_insertion_point(field_mutable:rpc.Answer.questioner)
  return _internal_mutable_questioner();
}
inline const std::string& Answer::_internal_questioner() const {
  return questioner_.Get();
}
inline void Answer::_internal_set_questioner(const std::string& value) {
  
  questioner_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, value, GetArena());
}
inline void Answer::set_questioner(std::string&& value) {
  
  questioner_.Set(
    ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, ::std::move(value), GetArena());
  // @@protoc_insertion_point(field_set_rvalue:rpc.Answer.questioner)
}
inline void Answer::set_questioner(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  questioner_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, ::std::string(value), GetArena());
  // @@protoc_insertion_point(field_set_char:rpc.Answer.questioner)
}
inline void Answer::set_questioner(const char* value,
    size_t size) {
  
  questioner_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, ::std::string(
      reinterpret_cast<const char*>(value), size), GetArena());
  // @@protoc_insertion_point(field_set_pointer:rpc.Answer.questioner)
}
inline std::string* Answer::_internal_mutable_questioner() {
  
  return questioner_.Mutable(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, GetArena());
}
inline std::string* Answer::release_questioner() {
  // @@protoc_insertion_point(field_release:rpc.Answer.questioner)
  return questioner_.Release(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
}
inline void Answer::set_allocated_questioner(std::string* questioner) {
  if (questioner != nullptr) {
    
  } else {
    
  }
  questioner_.SetAllocated(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), questioner,
      GetArena());
  // @@protoc_insertion_point(field_set_allocated:rpc.Answer.questioner)
}

// string answerer = 3;
inline void Answer::clear_answerer() {
  answerer_.ClearToEmpty();
}
inline const std::string& Answer::answerer() const {
  // @@protoc_insertion_point(field_get:rpc.Answer.answerer)
  return _internal_answerer();
}
inline void Answer::set_answerer(const std::string& value) {
  _internal_set_answerer(value);
  // @@protoc_insertion_point(field_set:rpc.Answer.answerer)
}
inline std::string* Answer::mutable_answerer() {
  // @@protoc_insertion_point(field_mutable:rpc.Answer.answerer)
  return _internal_mutable_answerer();
}
inline const std::string& Answer::_internal_answerer() const {
  return answerer_.Get();
}
inline void Answer::_internal_set_answerer(const std::string& value) {
  
  answerer_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, value, GetArena());
}
inline void Answer::set_answerer(std::string&& value) {
  
  answerer_.Set(
    ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, ::std::move(value), GetArena());
  // @@protoc_insertion_point(field_set_rvalue:rpc.Answer.answerer)
}
inline void Answer::set_answerer(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  answerer_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, ::std::string(value), GetArena());
  // @@protoc_insertion_point(field_set_char:rpc.Answer.answerer)
}
inline void Answer::set_answerer(const char* value,
    size_t size) {
  
  answerer_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, ::std::string(
      reinterpret_cast<const char*>(value), size), GetArena());
  // @@protoc_insertion_point(field_set_pointer:rpc.Answer.answerer)
}
inline std::string* Answer::_internal_mutable_answerer() {
  
  return answerer_.Mutable(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, GetArena());
}
inline std::string* Answer::release_answerer() {
  // @@protoc_insertion_point(field_release:rpc.Answer.answerer)
  return answerer_.Release(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
}
inline void Answer::set_allocated_answerer(std::string* answerer) {
  if (answerer != nullptr) {
    
  } else {
    
  }
  answerer_.SetAllocated(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), answerer,
      GetArena());
  // @@protoc_insertion_point(field_set_allocated:rpc.Answer.answerer)
}

// repeated string solution = 4;
inline int Answer::_internal_solution_size() const {
  return solution_.size();
}
inline int Answer::solution_size() const {
  return _internal_solution_size();
}
inline void Answer::clear_solution() {
  solution_.Clear();
}
inline std::string* Answer::add_solution() {
  // @@protoc_insertion_point(field_add_mutable:rpc.Answer.solution)
  return _internal_add_solution();
}
inline const std::string& Answer::_internal_solution(int index) const {
  return solution_.Get(index);
}
inline const std::string& Answer::solution(int index) const {
  // @@protoc_insertion_point(field_get:rpc.Answer.solution)
  return _internal_solution(index);
}
inline std::string* Answer::mutable_solution(int index) {
  // @@protoc_insertion_point(field_mutable:rpc.Answer.solution)
  return solution_.Mutable(index);
}
inline void Answer::set_solution(int index, const std::string& value) {
  // @@protoc_insertion_point(field_set:rpc.Answer.solution)
  solution_.Mutable(index)->assign(value);
}
inline void Answer::set_solution(int index, std::string&& value) {
  // @@protoc_insertion_point(field_set:rpc.Answer.solution)
  solution_.Mutable(index)->assign(std::move(value));
}
inline void Answer::set_solution(int index, const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  solution_.Mutable(index)->assign(value);
  // @@protoc_insertion_point(field_set_char:rpc.Answer.solution)
}
inline void Answer::set_solution(int index, const char* value, size_t size) {
  solution_.Mutable(index)->assign(
    reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:rpc.Answer.solution)
}
inline std::string* Answer::_internal_add_solution() {
  return solution_.Add();
}
inline void Answer::add_solution(const std::string& value) {
  solution_.Add()->assign(value);
  // @@protoc_insertion_point(field_add:rpc.Answer.solution)
}
inline void Answer::add_solution(std::string&& value) {
  solution_.Add(std::move(value));
  // @@protoc_insertion_point(field_add:rpc.Answer.solution)
}
inline void Answer::add_solution(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  solution_.Add()->assign(value);
  // @@protoc_insertion_point(field_add_char:rpc.Answer.solution)
}
inline void Answer::add_solution(const char* value, size_t size) {
  solution_.Add()->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_add_pointer:rpc.Answer.solution)
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField<std::string>&
Answer::solution() const {
  // @@protoc_insertion_point(field_list:rpc.Answer.solution)
  return solution_;
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField<std::string>*
Answer::mutable_solution() {
  // @@protoc_insertion_point(field_mutable_list:rpc.Answer.solution)
  return &solution_;
}

// -------------------------------------------------------------------

// Empty

// int32 id = 2;
inline bool Empty::_internal_has_id() const {
  bool value = (_has_bits_[0] & 0x00000001u) != 0;
  return value;
}
inline bool Empty::has_id() const {
  return _internal_has_id();
}
inline void Empty::clear_id() {
  id_ = 0;
  _has_bits_[0] &= ~0x00000001u;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 Empty::_internal_id() const {
  return id_;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 Empty::id() const {
  // @@protoc_insertion_point(field_get:rpc.Empty.id)
  return _internal_id();
}
inline void Empty::_internal_set_id(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _has_bits_[0] |= 0x00000001u;
  id_ = value;
}
inline void Empty::set_id(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _internal_set_id(value);
  // @@protoc_insertion_point(field_set:rpc.Empty.id)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------

// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace rpc

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_query_2eproto
