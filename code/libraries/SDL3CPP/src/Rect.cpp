#include "SDL3CPP/Rect.h"

using namespace SDL3CPP;

Rect Rect::GetUnion(const Rect &rect) const
{
    return Rect::FromCorners(std::min(x, rect.x), std::min(y, rect.y), std::max(GetX2(), rect.GetX2()),
                             std::max(GetY2(), rect.GetY2()));
}

Rect &Rect::Union(const Rect &rect)
{
    int nx = std::min(x, rect.x);
    int ny = std::min(y, rect.y);
    int nx2 = std::max(GetX2(), rect.GetX2());
    int ny2 = std::max(GetY2(), rect.GetY2());
    x = nx;
    y = ny;
    SetX2(nx2);
    SetY2(ny2);
    return *this;
}

Rect Rect::GetExtension(unsigned int amount) const
{
    Rect r = *this;
    r.Extend(amount);
    return r;
}

Rect Rect::GetExtension(unsigned int hamount, unsigned int vamount) const
{
    Rect r = *this;
    r.Extend(hamount, vamount);
    return r;
}

Rect &Rect::Extend(unsigned int amount)
{
    return Extend(amount, amount);
}

Rect &Rect::Extend(unsigned int hamount, unsigned int vamount)
{
    x -= hamount;
    y -= vamount;
    w += hamount * 2;
    h += vamount * 2;
    return *this;
}

Optional<Rect> Rect::GetIntersection(const Rect &rect) const
{
    if (!Intersects(rect))
        return NullOpt;

    return Rect::FromCorners(std::max(x, rect.x), std::max(y, rect.y), std::min(GetX2(), rect.GetX2()),
                             std::min(GetY2(), rect.GetY2()));
}

bool Rect::IntersectLine(int &x1, int &y1, int &x2, int &y2) const
{
    return SDL_GetRectAndLineIntersection(this, &x1, &y1, &x2, &y2);
}

bool Rect::IntersectLine(Point &p1, Point &p2) const
{
    return SDL_GetRectAndLineIntersection(this, &p1.x, &p1.y, &p2.x, &p2.y);
}

std::ostream &operator<<(std::ostream &stream, const Rect &rect)
{
    stream << "[x:" << rect.x << ",y:" << rect.y << ",w:" << rect.w << ",h:" << rect.h << "]";
    return stream;
}
