#pragma once

namespace L1
{
namespace L2
{
struct NameSpaceStruct
{
    int a;
};

}
}

L1::L2::NameSpaceStruct funParamNamespace(L1::L2::NameSpaceStruct param);
