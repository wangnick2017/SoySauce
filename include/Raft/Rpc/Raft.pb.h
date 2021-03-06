// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Raft.proto

#ifndef PROTOBUF_Raft_2eproto__INCLUDED
#define PROTOBUF_Raft_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3005000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3005001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
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
// @@protoc_insertion_point(includes)

namespace protobuf_Raft_2eproto {
// Internal implementation detail -- do not use these members.
struct TableStruct {
  static const ::google::protobuf::internal::ParseTableField entries[];
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[];
  static const ::google::protobuf::internal::ParseTable schema[4];
  static const ::google::protobuf::internal::FieldMetadata field_metadata[];
  static const ::google::protobuf::internal::SerializationTable serialization_table[];
  static const ::google::protobuf::uint32 offsets[];
};
void AddDescriptors();
void InitDefaultsReplyImpl();
void InitDefaultsReply();
void InitDefaultsEntryImpl();
void InitDefaultsEntry();
void InitDefaultsAppendEntriesMessageImpl();
void InitDefaultsAppendEntriesMessage();
void InitDefaultsRequestVoteMessageImpl();
void InitDefaultsRequestVoteMessage();
inline void InitDefaults() {
  InitDefaultsReply();
  InitDefaultsEntry();
  InitDefaultsAppendEntriesMessage();
  InitDefaultsRequestVoteMessage();
}
}  // namespace protobuf_Raft_2eproto
namespace Soy {
namespace Raft {
namespace Rpc {
class AppendEntriesMessage;
class AppendEntriesMessageDefaultTypeInternal;
extern AppendEntriesMessageDefaultTypeInternal _AppendEntriesMessage_default_instance_;
class Entry;
class EntryDefaultTypeInternal;
extern EntryDefaultTypeInternal _Entry_default_instance_;
class Reply;
class ReplyDefaultTypeInternal;
extern ReplyDefaultTypeInternal _Reply_default_instance_;
class RequestVoteMessage;
class RequestVoteMessageDefaultTypeInternal;
extern RequestVoteMessageDefaultTypeInternal _RequestVoteMessage_default_instance_;
}  // namespace Rpc
}  // namespace Raft
}  // namespace Soy
namespace Soy {
namespace Raft {
namespace Rpc {

// ===================================================================

class Reply : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:Soy.Raft.Rpc.Reply) */ {
 public:
  Reply();
  virtual ~Reply();

  Reply(const Reply& from);

  inline Reply& operator=(const Reply& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  Reply(Reply&& from) noexcept
    : Reply() {
    *this = ::std::move(from);
  }

  inline Reply& operator=(Reply&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const Reply& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const Reply* internal_default_instance() {
    return reinterpret_cast<const Reply*>(
               &_Reply_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    0;

  void Swap(Reply* other);
  friend void swap(Reply& a, Reply& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline Reply* New() const PROTOBUF_FINAL { return New(NULL); }

  Reply* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const Reply& from);
  void MergeFrom(const Reply& from);
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
  void InternalSwap(Reply* other);
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

  // uint64 term = 1;
  void clear_term();
  static const int kTermFieldNumber = 1;
  ::google::protobuf::uint64 term() const;
  void set_term(::google::protobuf::uint64 value);

  // bool ans = 2;
  void clear_ans();
  static const int kAnsFieldNumber = 2;
  bool ans() const;
  void set_ans(bool value);

  // @@protoc_insertion_point(class_scope:Soy.Raft.Rpc.Reply)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::uint64 term_;
  bool ans_;
  mutable int _cached_size_;
  friend struct ::protobuf_Raft_2eproto::TableStruct;
  friend void ::protobuf_Raft_2eproto::InitDefaultsReplyImpl();
};
// -------------------------------------------------------------------

class Entry : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:Soy.Raft.Rpc.Entry) */ {
 public:
  Entry();
  virtual ~Entry();

  Entry(const Entry& from);

  inline Entry& operator=(const Entry& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  Entry(Entry&& from) noexcept
    : Entry() {
    *this = ::std::move(from);
  }

  inline Entry& operator=(Entry&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const Entry& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const Entry* internal_default_instance() {
    return reinterpret_cast<const Entry*>(
               &_Entry_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    1;

  void Swap(Entry* other);
  friend void swap(Entry& a, Entry& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline Entry* New() const PROTOBUF_FINAL { return New(NULL); }

  Entry* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const Entry& from);
  void MergeFrom(const Entry& from);
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
  void InternalSwap(Entry* other);
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

  // string key = 2;
  void clear_key();
  static const int kKeyFieldNumber = 2;
  const ::std::string& key() const;
  void set_key(const ::std::string& value);
  #if LANG_CXX11
  void set_key(::std::string&& value);
  #endif
  void set_key(const char* value);
  void set_key(const char* value, size_t size);
  ::std::string* mutable_key();
  ::std::string* release_key();
  void set_allocated_key(::std::string* key);

  // string args = 3;
  void clear_args();
  static const int kArgsFieldNumber = 3;
  const ::std::string& args() const;
  void set_args(const ::std::string& value);
  #if LANG_CXX11
  void set_args(::std::string&& value);
  #endif
  void set_args(const char* value);
  void set_args(const char* value, size_t size);
  ::std::string* mutable_args();
  ::std::string* release_args();
  void set_allocated_args(::std::string* args);

  // uint64 term = 1;
  void clear_term();
  static const int kTermFieldNumber = 1;
  ::google::protobuf::uint64 term() const;
  void set_term(::google::protobuf::uint64 value);

  // @@protoc_insertion_point(class_scope:Soy.Raft.Rpc.Entry)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr key_;
  ::google::protobuf::internal::ArenaStringPtr args_;
  ::google::protobuf::uint64 term_;
  mutable int _cached_size_;
  friend struct ::protobuf_Raft_2eproto::TableStruct;
  friend void ::protobuf_Raft_2eproto::InitDefaultsEntryImpl();
};
// -------------------------------------------------------------------

class AppendEntriesMessage : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:Soy.Raft.Rpc.AppendEntriesMessage) */ {
 public:
  AppendEntriesMessage();
  virtual ~AppendEntriesMessage();

  AppendEntriesMessage(const AppendEntriesMessage& from);

  inline AppendEntriesMessage& operator=(const AppendEntriesMessage& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  AppendEntriesMessage(AppendEntriesMessage&& from) noexcept
    : AppendEntriesMessage() {
    *this = ::std::move(from);
  }

  inline AppendEntriesMessage& operator=(AppendEntriesMessage&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const AppendEntriesMessage& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const AppendEntriesMessage* internal_default_instance() {
    return reinterpret_cast<const AppendEntriesMessage*>(
               &_AppendEntriesMessage_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    2;

  void Swap(AppendEntriesMessage* other);
  friend void swap(AppendEntriesMessage& a, AppendEntriesMessage& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline AppendEntriesMessage* New() const PROTOBUF_FINAL { return New(NULL); }

  AppendEntriesMessage* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const AppendEntriesMessage& from);
  void MergeFrom(const AppendEntriesMessage& from);
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
  void InternalSwap(AppendEntriesMessage* other);
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

  // repeated .Soy.Raft.Rpc.Entry entries = 5;
  int entries_size() const;
  void clear_entries();
  static const int kEntriesFieldNumber = 5;
  const ::Soy::Raft::Rpc::Entry& entries(int index) const;
  ::Soy::Raft::Rpc::Entry* mutable_entries(int index);
  ::Soy::Raft::Rpc::Entry* add_entries();
  ::google::protobuf::RepeatedPtrField< ::Soy::Raft::Rpc::Entry >*
      mutable_entries();
  const ::google::protobuf::RepeatedPtrField< ::Soy::Raft::Rpc::Entry >&
      entries() const;

  // string leaderID = 2;
  void clear_leaderid();
  static const int kLeaderIDFieldNumber = 2;
  const ::std::string& leaderid() const;
  void set_leaderid(const ::std::string& value);
  #if LANG_CXX11
  void set_leaderid(::std::string&& value);
  #endif
  void set_leaderid(const char* value);
  void set_leaderid(const char* value, size_t size);
  ::std::string* mutable_leaderid();
  ::std::string* release_leaderid();
  void set_allocated_leaderid(::std::string* leaderid);

  // uint64 term = 1;
  void clear_term();
  static const int kTermFieldNumber = 1;
  ::google::protobuf::uint64 term() const;
  void set_term(::google::protobuf::uint64 value);

  // int64 prevLogIndex = 3;
  void clear_prevlogindex();
  static const int kPrevLogIndexFieldNumber = 3;
  ::google::protobuf::int64 prevlogindex() const;
  void set_prevlogindex(::google::protobuf::int64 value);

  // uint64 prevLogTerm = 4;
  void clear_prevlogterm();
  static const int kPrevLogTermFieldNumber = 4;
  ::google::protobuf::uint64 prevlogterm() const;
  void set_prevlogterm(::google::protobuf::uint64 value);

  // int64 leaderCommit = 6;
  void clear_leadercommit();
  static const int kLeaderCommitFieldNumber = 6;
  ::google::protobuf::int64 leadercommit() const;
  void set_leadercommit(::google::protobuf::int64 value);

  // @@protoc_insertion_point(class_scope:Soy.Raft.Rpc.AppendEntriesMessage)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::RepeatedPtrField< ::Soy::Raft::Rpc::Entry > entries_;
  ::google::protobuf::internal::ArenaStringPtr leaderid_;
  ::google::protobuf::uint64 term_;
  ::google::protobuf::int64 prevlogindex_;
  ::google::protobuf::uint64 prevlogterm_;
  ::google::protobuf::int64 leadercommit_;
  mutable int _cached_size_;
  friend struct ::protobuf_Raft_2eproto::TableStruct;
  friend void ::protobuf_Raft_2eproto::InitDefaultsAppendEntriesMessageImpl();
};
// -------------------------------------------------------------------

class RequestVoteMessage : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:Soy.Raft.Rpc.RequestVoteMessage) */ {
 public:
  RequestVoteMessage();
  virtual ~RequestVoteMessage();

  RequestVoteMessage(const RequestVoteMessage& from);

  inline RequestVoteMessage& operator=(const RequestVoteMessage& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  RequestVoteMessage(RequestVoteMessage&& from) noexcept
    : RequestVoteMessage() {
    *this = ::std::move(from);
  }

  inline RequestVoteMessage& operator=(RequestVoteMessage&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const RequestVoteMessage& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const RequestVoteMessage* internal_default_instance() {
    return reinterpret_cast<const RequestVoteMessage*>(
               &_RequestVoteMessage_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    3;

  void Swap(RequestVoteMessage* other);
  friend void swap(RequestVoteMessage& a, RequestVoteMessage& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline RequestVoteMessage* New() const PROTOBUF_FINAL { return New(NULL); }

  RequestVoteMessage* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const RequestVoteMessage& from);
  void MergeFrom(const RequestVoteMessage& from);
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
  void InternalSwap(RequestVoteMessage* other);
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

  // string candidateID = 2;
  void clear_candidateid();
  static const int kCandidateIDFieldNumber = 2;
  const ::std::string& candidateid() const;
  void set_candidateid(const ::std::string& value);
  #if LANG_CXX11
  void set_candidateid(::std::string&& value);
  #endif
  void set_candidateid(const char* value);
  void set_candidateid(const char* value, size_t size);
  ::std::string* mutable_candidateid();
  ::std::string* release_candidateid();
  void set_allocated_candidateid(::std::string* candidateid);

  // uint64 term = 1;
  void clear_term();
  static const int kTermFieldNumber = 1;
  ::google::protobuf::uint64 term() const;
  void set_term(::google::protobuf::uint64 value);

  // int64 lastLogIndex = 3;
  void clear_lastlogindex();
  static const int kLastLogIndexFieldNumber = 3;
  ::google::protobuf::int64 lastlogindex() const;
  void set_lastlogindex(::google::protobuf::int64 value);

  // uint64 lastLogTerm = 4;
  void clear_lastlogterm();
  static const int kLastLogTermFieldNumber = 4;
  ::google::protobuf::uint64 lastlogterm() const;
  void set_lastlogterm(::google::protobuf::uint64 value);

  // @@protoc_insertion_point(class_scope:Soy.Raft.Rpc.RequestVoteMessage)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr candidateid_;
  ::google::protobuf::uint64 term_;
  ::google::protobuf::int64 lastlogindex_;
  ::google::protobuf::uint64 lastlogterm_;
  mutable int _cached_size_;
  friend struct ::protobuf_Raft_2eproto::TableStruct;
  friend void ::protobuf_Raft_2eproto::InitDefaultsRequestVoteMessageImpl();
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// Reply

// uint64 term = 1;
inline void Reply::clear_term() {
  term_ = GOOGLE_ULONGLONG(0);
}
inline ::google::protobuf::uint64 Reply::term() const {
  // @@protoc_insertion_point(field_get:Soy.Raft.Rpc.Reply.term)
  return term_;
}
inline void Reply::set_term(::google::protobuf::uint64 value) {
  
  term_ = value;
  // @@protoc_insertion_point(field_set:Soy.Raft.Rpc.Reply.term)
}

// bool ans = 2;
inline void Reply::clear_ans() {
  ans_ = false;
}
inline bool Reply::ans() const {
  // @@protoc_insertion_point(field_get:Soy.Raft.Rpc.Reply.ans)
  return ans_;
}
inline void Reply::set_ans(bool value) {
  
  ans_ = value;
  // @@protoc_insertion_point(field_set:Soy.Raft.Rpc.Reply.ans)
}

// -------------------------------------------------------------------

// Entry

// uint64 term = 1;
inline void Entry::clear_term() {
  term_ = GOOGLE_ULONGLONG(0);
}
inline ::google::protobuf::uint64 Entry::term() const {
  // @@protoc_insertion_point(field_get:Soy.Raft.Rpc.Entry.term)
  return term_;
}
inline void Entry::set_term(::google::protobuf::uint64 value) {
  
  term_ = value;
  // @@protoc_insertion_point(field_set:Soy.Raft.Rpc.Entry.term)
}

// string key = 2;
inline void Entry::clear_key() {
  key_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& Entry::key() const {
  // @@protoc_insertion_point(field_get:Soy.Raft.Rpc.Entry.key)
  return key_.GetNoArena();
}
inline void Entry::set_key(const ::std::string& value) {
  
  key_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:Soy.Raft.Rpc.Entry.key)
}
#if LANG_CXX11
inline void Entry::set_key(::std::string&& value) {
  
  key_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:Soy.Raft.Rpc.Entry.key)
}
#endif
inline void Entry::set_key(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  key_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:Soy.Raft.Rpc.Entry.key)
}
inline void Entry::set_key(const char* value, size_t size) {
  
  key_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:Soy.Raft.Rpc.Entry.key)
}
inline ::std::string* Entry::mutable_key() {
  
  // @@protoc_insertion_point(field_mutable:Soy.Raft.Rpc.Entry.key)
  return key_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* Entry::release_key() {
  // @@protoc_insertion_point(field_release:Soy.Raft.Rpc.Entry.key)
  
  return key_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Entry::set_allocated_key(::std::string* key) {
  if (key != NULL) {
    
  } else {
    
  }
  key_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), key);
  // @@protoc_insertion_point(field_set_allocated:Soy.Raft.Rpc.Entry.key)
}

// string args = 3;
inline void Entry::clear_args() {
  args_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& Entry::args() const {
  // @@protoc_insertion_point(field_get:Soy.Raft.Rpc.Entry.args)
  return args_.GetNoArena();
}
inline void Entry::set_args(const ::std::string& value) {
  
  args_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:Soy.Raft.Rpc.Entry.args)
}
#if LANG_CXX11
inline void Entry::set_args(::std::string&& value) {
  
  args_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:Soy.Raft.Rpc.Entry.args)
}
#endif
inline void Entry::set_args(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  args_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:Soy.Raft.Rpc.Entry.args)
}
inline void Entry::set_args(const char* value, size_t size) {
  
  args_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:Soy.Raft.Rpc.Entry.args)
}
inline ::std::string* Entry::mutable_args() {
  
  // @@protoc_insertion_point(field_mutable:Soy.Raft.Rpc.Entry.args)
  return args_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* Entry::release_args() {
  // @@protoc_insertion_point(field_release:Soy.Raft.Rpc.Entry.args)
  
  return args_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Entry::set_allocated_args(::std::string* args) {
  if (args != NULL) {
    
  } else {
    
  }
  args_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), args);
  // @@protoc_insertion_point(field_set_allocated:Soy.Raft.Rpc.Entry.args)
}

// -------------------------------------------------------------------

// AppendEntriesMessage

// uint64 term = 1;
inline void AppendEntriesMessage::clear_term() {
  term_ = GOOGLE_ULONGLONG(0);
}
inline ::google::protobuf::uint64 AppendEntriesMessage::term() const {
  // @@protoc_insertion_point(field_get:Soy.Raft.Rpc.AppendEntriesMessage.term)
  return term_;
}
inline void AppendEntriesMessage::set_term(::google::protobuf::uint64 value) {
  
  term_ = value;
  // @@protoc_insertion_point(field_set:Soy.Raft.Rpc.AppendEntriesMessage.term)
}

// string leaderID = 2;
inline void AppendEntriesMessage::clear_leaderid() {
  leaderid_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& AppendEntriesMessage::leaderid() const {
  // @@protoc_insertion_point(field_get:Soy.Raft.Rpc.AppendEntriesMessage.leaderID)
  return leaderid_.GetNoArena();
}
inline void AppendEntriesMessage::set_leaderid(const ::std::string& value) {
  
  leaderid_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:Soy.Raft.Rpc.AppendEntriesMessage.leaderID)
}
#if LANG_CXX11
inline void AppendEntriesMessage::set_leaderid(::std::string&& value) {
  
  leaderid_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:Soy.Raft.Rpc.AppendEntriesMessage.leaderID)
}
#endif
inline void AppendEntriesMessage::set_leaderid(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  leaderid_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:Soy.Raft.Rpc.AppendEntriesMessage.leaderID)
}
inline void AppendEntriesMessage::set_leaderid(const char* value, size_t size) {
  
  leaderid_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:Soy.Raft.Rpc.AppendEntriesMessage.leaderID)
}
inline ::std::string* AppendEntriesMessage::mutable_leaderid() {
  
  // @@protoc_insertion_point(field_mutable:Soy.Raft.Rpc.AppendEntriesMessage.leaderID)
  return leaderid_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* AppendEntriesMessage::release_leaderid() {
  // @@protoc_insertion_point(field_release:Soy.Raft.Rpc.AppendEntriesMessage.leaderID)
  
  return leaderid_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void AppendEntriesMessage::set_allocated_leaderid(::std::string* leaderid) {
  if (leaderid != NULL) {
    
  } else {
    
  }
  leaderid_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), leaderid);
  // @@protoc_insertion_point(field_set_allocated:Soy.Raft.Rpc.AppendEntriesMessage.leaderID)
}

// int64 prevLogIndex = 3;
inline void AppendEntriesMessage::clear_prevlogindex() {
  prevlogindex_ = GOOGLE_LONGLONG(0);
}
inline ::google::protobuf::int64 AppendEntriesMessage::prevlogindex() const {
  // @@protoc_insertion_point(field_get:Soy.Raft.Rpc.AppendEntriesMessage.prevLogIndex)
  return prevlogindex_;
}
inline void AppendEntriesMessage::set_prevlogindex(::google::protobuf::int64 value) {
  
  prevlogindex_ = value;
  // @@protoc_insertion_point(field_set:Soy.Raft.Rpc.AppendEntriesMessage.prevLogIndex)
}

// uint64 prevLogTerm = 4;
inline void AppendEntriesMessage::clear_prevlogterm() {
  prevlogterm_ = GOOGLE_ULONGLONG(0);
}
inline ::google::protobuf::uint64 AppendEntriesMessage::prevlogterm() const {
  // @@protoc_insertion_point(field_get:Soy.Raft.Rpc.AppendEntriesMessage.prevLogTerm)
  return prevlogterm_;
}
inline void AppendEntriesMessage::set_prevlogterm(::google::protobuf::uint64 value) {
  
  prevlogterm_ = value;
  // @@protoc_insertion_point(field_set:Soy.Raft.Rpc.AppendEntriesMessage.prevLogTerm)
}

// repeated .Soy.Raft.Rpc.Entry entries = 5;
inline int AppendEntriesMessage::entries_size() const {
  return entries_.size();
}
inline void AppendEntriesMessage::clear_entries() {
  entries_.Clear();
}
inline const ::Soy::Raft::Rpc::Entry& AppendEntriesMessage::entries(int index) const {
  // @@protoc_insertion_point(field_get:Soy.Raft.Rpc.AppendEntriesMessage.entries)
  return entries_.Get(index);
}
inline ::Soy::Raft::Rpc::Entry* AppendEntriesMessage::mutable_entries(int index) {
  // @@protoc_insertion_point(field_mutable:Soy.Raft.Rpc.AppendEntriesMessage.entries)
  return entries_.Mutable(index);
}
inline ::Soy::Raft::Rpc::Entry* AppendEntriesMessage::add_entries() {
  // @@protoc_insertion_point(field_add:Soy.Raft.Rpc.AppendEntriesMessage.entries)
  return entries_.Add();
}
inline ::google::protobuf::RepeatedPtrField< ::Soy::Raft::Rpc::Entry >*
AppendEntriesMessage::mutable_entries() {
  // @@protoc_insertion_point(field_mutable_list:Soy.Raft.Rpc.AppendEntriesMessage.entries)
  return &entries_;
}
inline const ::google::protobuf::RepeatedPtrField< ::Soy::Raft::Rpc::Entry >&
AppendEntriesMessage::entries() const {
  // @@protoc_insertion_point(field_list:Soy.Raft.Rpc.AppendEntriesMessage.entries)
  return entries_;
}

// int64 leaderCommit = 6;
inline void AppendEntriesMessage::clear_leadercommit() {
  leadercommit_ = GOOGLE_LONGLONG(0);
}
inline ::google::protobuf::int64 AppendEntriesMessage::leadercommit() const {
  // @@protoc_insertion_point(field_get:Soy.Raft.Rpc.AppendEntriesMessage.leaderCommit)
  return leadercommit_;
}
inline void AppendEntriesMessage::set_leadercommit(::google::protobuf::int64 value) {
  
  leadercommit_ = value;
  // @@protoc_insertion_point(field_set:Soy.Raft.Rpc.AppendEntriesMessage.leaderCommit)
}

// -------------------------------------------------------------------

// RequestVoteMessage

// uint64 term = 1;
inline void RequestVoteMessage::clear_term() {
  term_ = GOOGLE_ULONGLONG(0);
}
inline ::google::protobuf::uint64 RequestVoteMessage::term() const {
  // @@protoc_insertion_point(field_get:Soy.Raft.Rpc.RequestVoteMessage.term)
  return term_;
}
inline void RequestVoteMessage::set_term(::google::protobuf::uint64 value) {
  
  term_ = value;
  // @@protoc_insertion_point(field_set:Soy.Raft.Rpc.RequestVoteMessage.term)
}

// string candidateID = 2;
inline void RequestVoteMessage::clear_candidateid() {
  candidateid_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& RequestVoteMessage::candidateid() const {
  // @@protoc_insertion_point(field_get:Soy.Raft.Rpc.RequestVoteMessage.candidateID)
  return candidateid_.GetNoArena();
}
inline void RequestVoteMessage::set_candidateid(const ::std::string& value) {
  
  candidateid_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:Soy.Raft.Rpc.RequestVoteMessage.candidateID)
}
#if LANG_CXX11
inline void RequestVoteMessage::set_candidateid(::std::string&& value) {
  
  candidateid_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:Soy.Raft.Rpc.RequestVoteMessage.candidateID)
}
#endif
inline void RequestVoteMessage::set_candidateid(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  candidateid_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:Soy.Raft.Rpc.RequestVoteMessage.candidateID)
}
inline void RequestVoteMessage::set_candidateid(const char* value, size_t size) {
  
  candidateid_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:Soy.Raft.Rpc.RequestVoteMessage.candidateID)
}
inline ::std::string* RequestVoteMessage::mutable_candidateid() {
  
  // @@protoc_insertion_point(field_mutable:Soy.Raft.Rpc.RequestVoteMessage.candidateID)
  return candidateid_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* RequestVoteMessage::release_candidateid() {
  // @@protoc_insertion_point(field_release:Soy.Raft.Rpc.RequestVoteMessage.candidateID)
  
  return candidateid_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void RequestVoteMessage::set_allocated_candidateid(::std::string* candidateid) {
  if (candidateid != NULL) {
    
  } else {
    
  }
  candidateid_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), candidateid);
  // @@protoc_insertion_point(field_set_allocated:Soy.Raft.Rpc.RequestVoteMessage.candidateID)
}

// int64 lastLogIndex = 3;
inline void RequestVoteMessage::clear_lastlogindex() {
  lastlogindex_ = GOOGLE_LONGLONG(0);
}
inline ::google::protobuf::int64 RequestVoteMessage::lastlogindex() const {
  // @@protoc_insertion_point(field_get:Soy.Raft.Rpc.RequestVoteMessage.lastLogIndex)
  return lastlogindex_;
}
inline void RequestVoteMessage::set_lastlogindex(::google::protobuf::int64 value) {
  
  lastlogindex_ = value;
  // @@protoc_insertion_point(field_set:Soy.Raft.Rpc.RequestVoteMessage.lastLogIndex)
}

// uint64 lastLogTerm = 4;
inline void RequestVoteMessage::clear_lastlogterm() {
  lastlogterm_ = GOOGLE_ULONGLONG(0);
}
inline ::google::protobuf::uint64 RequestVoteMessage::lastlogterm() const {
  // @@protoc_insertion_point(field_get:Soy.Raft.Rpc.RequestVoteMessage.lastLogTerm)
  return lastlogterm_;
}
inline void RequestVoteMessage::set_lastlogterm(::google::protobuf::uint64 value) {
  
  lastlogterm_ = value;
  // @@protoc_insertion_point(field_set:Soy.Raft.Rpc.RequestVoteMessage.lastLogTerm)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------

// -------------------------------------------------------------------

// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace Rpc
}  // namespace Raft
}  // namespace Soy

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_Raft_2eproto__INCLUDED
