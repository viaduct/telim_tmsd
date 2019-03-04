#pragma once

namespace telimtmsd {

class ItemType;
template <typename T> class ValueType;
class ObjType;
class ContType;
class SingleType;
class SetType;
class ListType;

class Item;
template <typename T> class Value;
class Obj;
class Cont;
class Single;
class Set;
class List;

class Track;
class ItemTrack;
template <typename T> class ValueTrack;
class ObjTrack;
class ContTrack;
class SingleTrack;
class SetTrack;
class ListTrack;

class TrackInfo;
class ItemTrackInfo;
template <typename T> class ValueTrackInfo;
class ObjTrackInfo;
class ContTrackInfo;
class SingleTrackInfo;
class SetTrackInfo;
class ListTrackInfo;

class Mimic;
class ItemMimic;
template <typename T> class ValueMimic;
class ObjMimic;
class ContMimic;
class SingleMimic;
class SetMimic;
class ListMimic;

template <typename T>
struct Chain
{
};

template <>
struct Chain<Item>
{
	using Type = ItemType;
	using Data = Item;
	using Track = ItemTrack;
	using TrackInfo = ItemTrackInfo;
	using Mimic = ItemMimic;
};

template <typename... Args>
struct Chain<Value<Args...>>
{
	using Type = ValueType<Args...>;
	using Data = Value<Args...>;
	using Track = ValueTrack<Args...>;
	using TrackInfo = ValueTrackInfo<Args...>;
	using Mimic = ValueMimic<Args...>;
};

template <>
struct Chain<Obj>
{
	using Type = ObjType;
	using Data = Obj;
	using Track = ObjTrack;
	using TrackInfo = ObjTrackInfo;
	using Mimic = ObjMimic;
};

template <>
struct Chain<Cont>
{
	using Type = ContType;
	using Data = Cont;
	using Track = ContTrack;
	using TrackInfo = ContTrackInfo;
	using Mimic = ContMimic;
};

template <>
struct Chain<Single>
{
	using Type = SingleType;
	using Data = Single;
	using Track = SingleTrack;
	using TrackInfo = SingleTrackInfo;
	using Mimic = SingleMimic;
};

template <>
struct Chain<Set>
{
	using Type = SetType;
	using Data = Set;
	using Track = SetTrack;
	using TrackInfo = SetTrackInfo;
	using Mimic = SetMimic;
};

template <>
struct Chain<List>
{
	using Type = ListType;
	using Data = List;
	using Track = ListTrack;
	using TrackInfo = ListTrackInfo;
	using Mimic = ListMimic;
};

template <>
struct Chain<typename Chain<Item>::Type> : Chain<Item>
{
};

template <>
struct Chain<typename Chain<Item>::Track> : Chain<Item>
{
};

template <>
struct Chain<typename Chain<Item>::TrackInfo> : Chain<Item>
{
};

template <>
struct Chain<typename Chain<Item>::Mimic> : Chain<Item>
{
};

template <typename... Args>
struct Chain<ValueType<Args...>> : Chain<Value<Args...>>
{
};

template <typename... Args>
struct Chain<ValueTrack<Args...>> : Chain<Value<Args...>>
{
};

template <typename... Args>
struct Chain<ValueTrackInfo<Args...>> : Chain<Value<Args...>>
{
};

template <typename... Args>
struct Chain<ValueMimic<Args...>> : Chain<Value<Args...>>
{
};

template <>
struct Chain<typename Chain<Obj>::Type> : Chain<Obj>
{
};

template <>
struct Chain<typename Chain<Obj>::Track> : Chain<Obj>
{
};

template <>
struct Chain<typename Chain<Obj>::TrackInfo> : Chain<Obj>
{
};

template <>
struct Chain<typename Chain<Obj>::Mimic> : Chain<Obj>
{
};

template <>
struct Chain<typename Chain<Cont>::Type> : Chain<Cont>
{
};

template <>
struct Chain<typename Chain<Cont>::Track> : Chain<Cont>
{
};

template <>
struct Chain<typename Chain<Cont>::TrackInfo> : Chain<Cont>
{
};

template <>
struct Chain<typename Chain<Cont>::Mimic> : Chain<Cont>
{
};

template <>
struct Chain<typename Chain<Single>::Type> : Chain<Single>
{
};

template <>
struct Chain<typename Chain<Single>::Track> : Chain<Single>
{
};

template <>
struct Chain<typename Chain<Single>::TrackInfo> : Chain<Single>
{
};

template <>
struct Chain<typename Chain<Single>::Mimic> : Chain<Single>
{
};

template <>
struct Chain<typename Chain<Set>::Type> : Chain<Set>
{
};

template <>
struct Chain<typename Chain<Set>::Track> : Chain<Set>
{
};

template <>
struct Chain<typename Chain<Set>::TrackInfo> : Chain<Set>
{
};

template <>
struct Chain<typename Chain<Set>::Mimic> : Chain<Set>
{
};

template <>
struct Chain<typename Chain<List>::Type> : Chain<List>
{
};

template <>
struct Chain<typename Chain<List>::Track> : Chain<List>
{
};

template <>
struct Chain<typename Chain<List>::TrackInfo> : Chain<List>
{
};

template <>
struct Chain<typename Chain<List>::Mimic> : Chain<List>
{
};

}
