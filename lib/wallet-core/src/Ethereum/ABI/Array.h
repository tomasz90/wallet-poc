// Copyright © 2017-2023 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#pragma once

#include "ParamBase.h"
#include "ParamNumber.h"
#include "Parameters.h"

namespace TW::Ethereum::ABI {

/// Dynamic array of the same types, "<type>[]"
/// Normally has at least one element.  Empty array can have prototype set so its type is known.
/// Empty with no prototype is possible, but should be avoided.
class ParamArray : public ParamCollection {
private:
    ParamSet _params;
    std::shared_ptr<ParamBase> _proto; // an optional prototype element, determines the array type, useful in empty array case

private:
    std::shared_ptr<ParamBase> getProtoElem() const; // the first element if exists, otherwise the proto element
    std::string getProtoType() const;

public:
    ParamArray() = default;
    ParamArray(const std::shared_ptr<ParamBase>& param1)
        : ParamCollection() { addParam(param1); }
    ParamArray(const std::vector<std::shared_ptr<ParamBase>>& params)
        : ParamCollection() { setVal(params); }
    void setVal(const std::vector<std::shared_ptr<ParamBase>>& params) { addParams(params); }
    std::vector<std::shared_ptr<ParamBase>> const& getVal() const { return _params.getParams(); }
    int addParam(const std::shared_ptr<ParamBase>& param);
    void addParams(const std::vector<std::shared_ptr<ParamBase>>& params);
    void setProto(const std::shared_ptr<ParamBase>& proto) { _proto = proto; }
    std::shared_ptr<ParamBase> getParam(int paramIndex) { return _params.getParamUnsafe(paramIndex); }
    virtual std::string getType() const { return getProtoType() + "[]"; }
    virtual size_t getSize() const;
    virtual bool isDynamic() const { return true; }
    virtual size_t getCount() const { return _params.getCount(); }
    virtual void encode(Data& data) const;
    virtual bool decode(const Data& encoded, size_t& offset_inout);
    virtual bool setValueJson(const std::string& value);
    virtual Data hashStruct() const;
    virtual std::string getExtraTypes(std::vector<std::string>& ignoreList) const;
};

/// Fixed-size array of the same type e.g, "type[4]"
class ParamArrayFix final : public ParamCollection {
public:
    //! Public Definitions
    using Params = std::vector<std::shared_ptr<ParamBase>>;

    //! Public constructor
    explicit ParamArrayFix(const Params& params) noexcept(false)
        : ParamCollection() {
        this->addParams(params);
    }

    //! Public member methods
    [[nodiscard]] std::size_t getCount() const final { return _params.getCount(); }
    [[nodiscard]] size_t getSize() const final { return _params.getSize(); }
    [[nodiscard]] bool isDynamic() const final { return false; }
    [[nodiscard]] std::string getType() const final { return _params.getParamUnsafe(0)->getType() + "[" + std::to_string(_params.getCount()) + "]"; }
    void encode(Data& data) const final;
    bool decode(const Data& encoded, size_t& offset_inout) final;
    bool setValueJson(const std::string& value) final;

private:
    //! Private member functions
    void addParams(const Params& params) noexcept(false);

    //! Private member fields
    ParamSet _params;
};

} // namespace TW::Ethereum::ABI
