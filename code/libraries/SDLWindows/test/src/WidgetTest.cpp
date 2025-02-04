#include "SDLWindows/Widget.h"

#include "test-platform/GoogleTest.h"
#include "SDL3CPP/SDL.h"

using namespace SDL3CPP;
using namespace SDLWindows;

class WidgetTest : public testing::Test
{
public:
    void SetUp() override;
    void TearDown() override;
};

void WidgetTest::SetUp()
{
}

void WidgetTest::TearDown()
{
}

TEST_F(WidgetTest, ConstructDefault)
{
    Widget widget;

    EXPECT_EQ(NullHandle, widget.GetParent());
    EXPECT_EQ("", widget.GetTitle());
    EXPECT_EQ(WidgetStyleFlags(WidgetStyle::None), widget.GetStyle());
    EXPECT_EQ(Rect(0, 0, 0, 0), widget.GetRect());
    EXPECT_EQ(Point(0, 0), widget.GetPosition());
    EXPECT_EQ(Size(0, 0), widget.GetSize());
}

