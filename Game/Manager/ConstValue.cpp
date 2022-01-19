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


    Difficulty operator++(Difficulty& d)
    {
        return d = (d == Difficulty::Hard) ? Difficulty::Hard : static_cast<Difficulty>(static_cast<int>(d) + 1);
    }
    Difficulty operator--(Difficulty& d)
    {
        return d = (d == Difficulty::Easy) ? Difficulty::Easy : static_cast<Difficulty>(static_cast<int>(d) - 1);
    }

    std::string const& ToString(Difficulty& d)
    {
        switch (d)
        {
            case Difficulty::Easy:
            {
                return StrDiffi[0];
            }
            case Difficulty::Normal:
            {
                return StrDiffi[1];
            }
            case Difficulty::Hard:
            {
                return StrDiffi[2];
            }
            default:
            {
                return StrDiffi[0];
            }
        }
    }
}

namespace Keycode
{
    std::string toString(size_t const& code)
    {
        std::map<size_t, std::string>::const_iterator it = KeyMap.find(code);
        if (it == KeyMap.end()) return "";
        return it->second;
    }
}