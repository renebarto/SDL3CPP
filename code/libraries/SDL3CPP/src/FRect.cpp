#include "SDL3CPP/FRect.h"

using namespace SDL3CPP;

FRect FRect::GetUnion(const FRect &rect) const
{
    return FRect::FromCorners(std::min(x, rect.x), std::min(y, rect.y), std::max(GetX2(), rect.GetX2()),
                             std::max(GetY2(), rect.GetY2()));
}

FRect &FRect::Union(const FRect &rect)
{
    float nx = std::min(x, rect.x);
    float ny = std::min(y, rect.y);
    float nx2 = std::max(GetX2(), rect.GetX2());
    float ny2 = std::max(GetY2(), rect.GetY2());
    x = nx;
    y = ny;
    SetX2(nx2);
    SetY2(ny2);
    return *this;
}

FRect FRect::GetExtension(float amount) const
{
    FRect r = *this;
    r.Extend(amount);
    return r;
}

FRect FRect::GetExtension(float hamount, float vamount) const
{
    FRect r = *this;
    r.Extend(hamount, vamount);
    return r;
}

FRect &FRect::Extend(float amount)
{
    return Extend(amount, amount);
}

FRect &FRect::Extend(float hamount, float vamount)
{
    x -= hamount;
    y -= vamount;
    w += hamount * 2;
    h += vamount * 2;
    return *this;
}

Optional<FRect> FRect::GetIntersection(const FRect &rect) const
{
    if (!Intersects(rect))
        return NullOpt;

    return FRect::FromCorners(std::max(x, rect.x), std::max(y, rect.y), std::min(GetX2(), rect.GetX2()),
                             std::min(GetY2(), rect.GetY2()));
}

std::ostream &operator<<(std::ostream &stream, const FRect &rect)
{
    stream << "[x:" << rect.x << ",y:" << rect.y << ",w:" << rect.w << ",h:" << rect.h << "]";
    return stream;
}
