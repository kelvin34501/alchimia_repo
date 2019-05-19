#ifndef SEREIALIZE_H
#define SEREIALIZE_H

#include <cereal/archives/json.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/array.hpp>
#include <cereal/types/map.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/polymorphic.hpp>

#include <graphmodel/graphmodel.h>
#include <converter/converter.h>

#include <QString>

// these things should be in root namespace for cereal to work
template <class Archive>
std::string save_minimal(Archive const &ar,
                         Backend const &m)
{
    switch (m)
    {
        case Backend::Keras: return "Keras";
        case Backend::Pytorch: return "Pytorch";
    }
    return "unset"; // Default value
}

template <class Archive> void load_minimal(Archive const &ar,
                                           Backend &m,
                                           std::string const &value)
{
    if (value == "Keras") m = Backend::Keras;
    else if (value == "Pytorch") m = Backend::Pytorch;
    else m = Backend::Keras; // Default value
}

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
               ProjectCFG &m)
{
    archive(cereal::make_nvp("name", m.name),
            cereal::make_nvp("location",m.location),
            cereal::make_nvp("pro_desc_path", m.pro_desc_path));
}

template <class Archive>
void serialize(Archive &archive,
               ModelCFG &m)
{
    archive(cereal::make_nvp("archi_path", m.archi_path),
            cereal::make_nvp("weight_path",m.weight_path));
}

template <class Archive>
void serialize(Archive &archive,
               DataCFG &m)
{
    archive(cereal::make_nvp("train_X_file", m.train_X_file),
            cereal::make_nvp("train_X_folder", m.train_X_folder),
            cereal::make_nvp("train_y_file", m.train_y_file),
            cereal::make_nvp("validate_X_file", m.validate_X_file),
            cereal::make_nvp("validate_X_folder", m.validate_X_folder),
            cereal::make_nvp("validate_y_file", m.validate_X_file),
            cereal::make_nvp("test_X_file", m.test_X_file),
            cereal::make_nvp("test_X_folder", m.test_X_folder),
            cereal::make_nvp("X_columns", m.X_columns),
            cereal::make_nvp("y_columns", m.y_columns));
}

template <class Archive>
void serialize(Archive &archive,
               GraphModel &m)
{
    archive(cereal::make_nvp("parts",m.parts),
            cereal::make_nvp("connections",m.connections),
            cereal::make_nvp("model_cfg",m.model_cfg),
            cereal::make_nvp("data_cfg",m.data_cfg),
            cereal::make_nvp("py_cvt",m.py_cvt));
}

CEREAL_REGISTER_TYPE(KerasConverter)
CEREAL_REGISTER_POLYMORPHIC_RELATION(PythonConverter, KerasConverter)

template <class Archive>
void serialize(Archive &archive,
               KerasConverter &m)
{
    // do nothing
    // need cereal to ensure type
}

template <class Archive>
void serialize(Archive &archive,
               CompileCFG &m)
{
    archive(cereal::make_nvp("archi_path", m.archi_path),
            cereal::make_nvp("pyfile_path",m.pyfile_path));
}

template <class Archive>
void serialize(Archive &archive,
               TBCFG &m)
{
    archive(cereal::make_nvp("log_dir", m.log_dir),
            cereal::make_nvp("histogram_freq",m.histogram_freq),
            cereal::make_nvp("update_freq",m.update_freq));
}

template <class Archive>
void serialize(Archive &archive,
               TrainCFG &m)
{
    archive(cereal::make_nvp("optimizer", m.optimizer),
            cereal::make_nvp("loss", m.loss),
            cereal::make_nvp("metrics", m.metrics),
            cereal::make_nvp("batch_size", m.batch_size),
            cereal::make_nvp("epochs", m.epochs),
            cereal::make_nvp("validation_split", m.validation_split),
            cereal::make_nvp("shuffle", m.shuffle),
            cereal::make_nvp("save_weight_path", m.save_weight_path),
            cereal::make_nvp("reuse_weight", m.reuse_weight),
            cereal::make_nvp("tb_cfg", m.tb_cfg));
}

template <class Archive>
void serialize(Archive &archive,
               TestCFG &m)
{
    // do nothing
}

// temp workaround for QString
template <class Archive>
void serialize(Archive &archive,
               QString &m)
{
    archive(m.toStdString());
}

#endif // SEREIALIZE_H
