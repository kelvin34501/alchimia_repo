#ifndef SEREIALIZE_H
#define SEREIALIZE_H

#include <cereal/archives/json.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/array.hpp>
#include <cereal/types/map.hpp>
#include <cereal/types/memory.hpp>

#include <graphmodel/graphmodel.h>

template <class Archive>
void serialize(Archive &archive,
               Port &m)
{
    archive(cereal::make_nvp("part",m.part),
            cereal::make_nvp("connection",m.connection),
            cereal::make_nvp("is_output",m.is_output),
            cereal::make_nvp("shape",m.shape));
}

template <class Archive>
void serialize(Archive &archive,
               Part &m)
{
    archive(cereal::make_nvp("part_id",m.id),
            cereal::make_nvp("ports",m.ports),
            cereal::make_nvp("params",m.params),
            cereal::make_nvp("parttype",m.parttype),
            cereal::make_nvp("position_x",m.position_x),
            cereal::make_nvp("position_y",m.position_y));
}

template <class Archive>
void serialize(Archive &archive,
               Connection &m)
{
    archive(cereal::make_nvp("connection_id",m.id),
            cereal::make_nvp("ports",m.ports));
}

template <class Archive>
void serialize(Archive &archive,
               GraphModel &m)
{
    archive(cereal::make_nvp("parts",m.parts),
            cereal::make_nvp("connections",m.connections));
}


#endif // SEREIALIZE_H
