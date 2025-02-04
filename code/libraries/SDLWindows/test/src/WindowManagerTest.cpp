#include "SDLWindows/WindowManager.h"

#include "test-platform/GoogleTest.h"
#include "SDL3CPP/SDL.h"

using namespace SDL3CPP;
using namespace SDLWindows;

class WindowManagerTest : public testing::Test
{
private:
    DisplayConfiguration m_displayConfiguration;
    DisplayID m_displayID;
    DisplayInfo m_displayInfo;

public:
    const DisplayID InvalidDisplayID = 100;
    void SetUp() override;
    void TearDown() override;

    const DisplayInfo &GetDisplayInfo() { return m_displayInfo; }
    DisplayID GetDisplayID() { return m_displayID; }
};

void WindowManagerTest::SetUp()
{
    m_displayConfiguration = Singleton<SDL3CPP::SDL>::Get().GetDisplayConfiguration();
    m_displayID = m_displayConfiguration.GetPrimaryDisplay();
    m_displayConfiguration.GetDisplayInfo(m_displayID, m_displayInfo);
}

void WindowManagerTest::TearDown()
{

}

TEST_F(WindowManagerTest, ConstructDefault)
{
    auto &manager = Singleton<WindowManager>::Get();

    EXPECT_EQ(Point(0, 0), manager.GetPosition());
    EXPECT_EQ(Size(GetDisplayInfo().w, GetDisplayInfo().h), manager.GetSize());
    EXPECT_FALSE(manager.IsFullScreen());
    EXPECT_EQ(GetDisplayID(), manager.GetDisplay());
}

TEST_F(WindowManagerTest, SetDisplayPrimarySucceeds)
{
    auto &manager = Singleton<WindowManager>::Get();

    EXPECT_TRUE(manager.SetDisplay(GetDisplayID()));

    EXPECT_EQ(Point(0, 0), manager.GetPosition());
    EXPECT_EQ(Size(GetDisplayInfo().w, GetDisplayInfo().h), manager.GetSize());
    EXPECT_FALSE(manager.IsFullScreen());
    EXPECT_EQ(GetDisplayID(), manager.GetDisplay());
}

TEST_F(WindowManagerTest, SetDisplayInvalidFails)
{
    auto &manager = Singleton<WindowManager>::Get();

    EXPECT_FALSE(manager.SetDisplay(InvalidDisplayID));

    EXPECT_EQ(Point(0, 0), manager.GetPosition());
    EXPECT_EQ(Size(GetDisplayInfo().w, GetDisplayInfo().h), manager.GetSize());
    EXPECT_FALSE(manager.IsFullScreen());
    EXPECT_EQ(GetDisplayID(), manager.GetDisplay());
}
