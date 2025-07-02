#pragma once

// This helper macro is used to declare typedefs. For example:
// 
// NOTE: VertCoords -> Vector<Vector3f, VertId>
// 
// The code below,
//     BIND_TYPED_VECTOR( VertCoords, Vector3f, VertId );
// 
// will generate the following code:
//     class_<VertCoords>( "VertCoords" )
//         .constructor<>()
//         .constructor<size_t>()
//         .constructor<size_t, const Vector3f&>()
//         .function( "size", &VertCoords::size )
//         .function( "get", select_overload<const Vector3f&(VertId) const>(&VertCoords::operator[]) )
//
#define BIND_TYPED_VECTOR(NAME, ELEM_TYPE, ID_TYPE) \
    class_<NAME>(#NAME) \
        .constructor<>() \
        .constructor<size_t>() \
        .constructor<size_t, const ELEM_TYPE&>() \
        .function("size", &NAME::size) \
        .function("empty", &NAME::empty) \
        .function("clear", &NAME::clear) \
        .function("capacity", &NAME::capacity) \
        .function("reserve", &NAME::reserve) \
        .function("resize", select_overload<void(size_t)>(&NAME::resize)) \
        .function("resizeWithValue", select_overload<void(size_t, const ELEM_TYPE&)>(&NAME::resize)) \
        .function("resizeWithReserve", select_overload<void(size_t)>(&NAME::resizeWithReserve)) \
        .function("resizeWithReserveAndValue", select_overload<void(size_t, const ELEM_TYPE&)>(&NAME::resizeWithReserve)) \
        .function("get", select_overload<const ELEM_TYPE&(ID_TYPE) const>(&NAME::operator[])) \
        .function("set", optional_override([](NAME& self, ID_TYPE i, ELEM_TYPE value) { self[i] = value; })) \
        .function("getByIndex", select_overload<const ELEM_TYPE&(ID_TYPE) const>(&NAME::operator[])) \
        .function("getByIndexMutable", select_overload<ELEM_TYPE&(ID_TYPE)>(&NAME::operator[]), allow_raw_pointers()) \
        .function("getAt", optional_override([](const NAME& self, ID_TYPE i) -> ELEM_TYPE { \
            if (i >= self.size()) throw std::out_of_range(std::string(#NAME) + " index out of range: " + std::to_string(int(i)) + " >= " + std::to_string(self.size())); \
            return self[i]; \
        })) \
        .function("setAt", optional_override([](NAME& self, ID_TYPE i, ELEM_TYPE value) -> bool { \
            if (i >= self.size()) throw std::out_of_range(std::string(#NAME) + " index out of range: " + std::to_string(int(i)) + " >= " + std::to_string(self.size())); \
            self[i] = value; return true; \
        })) \
        .function("front", select_overload<const ELEM_TYPE&() const>(&NAME::front)) \
        .function("frontMutable", select_overload<ELEM_TYPE&()>(&NAME::front), allow_raw_pointers()) \
        .function("back", select_overload<const ELEM_TYPE&() const>(&NAME::back)) \
        .function("backMutable", select_overload<ELEM_TYPE&()>(&NAME::back), allow_raw_pointers()) \
        .function("pushBack", select_overload<void(const ELEM_TYPE&)>(&NAME::push_back)) \
        .function("popBack", &NAME::pop_back) \
        .function("emplaceBack", &NAME::emplace_back<ELEM_TYPE>) \
        .function("beginId", &NAME::beginId) \
        .function("backId", &NAME::backId) \
        .function("endId", &NAME::endId) \
        .function("autoResizeAt", select_overload<ELEM_TYPE&(ID_TYPE)>(&NAME::autoResizeAt)) \
        .function("autoResizeSet", select_overload<void(ID_TYPE, ELEM_TYPE)>(&NAME::autoResizeSet)) \
        .function("autoResizeSetRange", select_overload<void(ID_TYPE, size_t, ELEM_TYPE)>(&NAME::autoResizeSet)) \
        .function("swap", &NAME::swap) \
        .function("heapBytes", &NAME::heapBytes) \
        .function("equals", optional_override([](const NAME& a, const NAME& b) { return a == b; })) \
        .function("notEquals", optional_override([](const NAME& a, const NAME& b) { return a != b; }));
