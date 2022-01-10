#include "stdafx.h"
#include "ConstValue.h"

namespace ConstValue
{
    SceneList operator++(SceneList& sl)
    {
        return sl = sl == SceneList::End ? SceneList::End : static_cast<SceneList>(static_cast<int>(sl) + 1);
    }
    SceneList operator--(SceneList& sl)
    {
        return sl = sl == SceneList::Title ? SceneList::Title : static_cast<SceneList>(static_cast<int>(sl) - 1);
    }

    bool operator<(SceneList& A, SceneList& B)
    {
        return static_cast<UINT> (A) < static_cast<UINT> (B);
    }

    OptionList operator++(OptionList& ol)
    {
        return ol = (ol == OptionList::Keys) ? OptionList::Keys : static_cast<OptionList>(static_cast<int>(ol) + 1);
    }
    OptionList operator--(OptionList& ol)
    {
        return ol = (ol == OptionList::Sync) ? OptionList::Sync : static_cast<OptionList>(static_cast<int>(ol) - 1);
    }

    bool operator<(OptionList& A, OptionList& B)
    {
        return static_cast<UINT> (A) < static_cast<UINT> (B);
    }
}