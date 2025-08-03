#include "Entity.hpp"
#include <ostream>
#define SDL_MAIN_HANDLED
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "gtest/gtest.h"
#include <stdexcept>

constexpr Color DUMMY_COLOR{ 0, 0, 0, 255 };

std::ostream &
operator<< (std::ostream &os, const Entity &entity)
{
  return os << "Entity: {" << entity.get_x () << ", " << entity.get_y ()
            << "}";
}

struct EntityTest : testing::Test
{
  Entity entity;
  EntityTest () : entity{ 0, 0, DUMMY_COLOR } {}
};

TEST_F (EntityTest, Collides)
{
  ASSERT_TRUE (entity.collides (Entity{ 0, 0, DUMMY_COLOR }));
}
TEST_F (EntityTest, DifferentX)
{
  ASSERT_FALSE (entity.collides (Entity{ 1, 0, DUMMY_COLOR }));
}
TEST_F (EntityTest, DifferentY)
{
  ASSERT_FALSE (entity.collides (Entity{ 0, 1, DUMMY_COLOR }));
}

struct EntityRenderFail : testing::Test
{
  SDL_Renderer *dummy_renderer = nullptr;
  SDL_FRect dummy_rect = { 1, 1, 1, 1 };
  int dummy_len = 50;
};

TEST_F (EntityRenderFail, BadRendererThrows)
{
  Entity entity (0, 0, DUMMY_COLOR);
  EXPECT_THROW (entity.render (*dummy_renderer, dummy_rect, dummy_len),
                std::runtime_error);
}

TEST_F(EntityRenderFail, RectNotSquareThrows) {
  Entity entity (0,0,DUMMY_COLOR);
  dummy_rect.h += dummy_rect.w;
  EXPECT_THROW (entity.render (*dummy_renderer, dummy_rect, dummy_len),
                std::logic_error);
}

struct EntityRenderFailParam : EntityRenderFail,
                               testing::WithParamInterface<Entity>
{
};

TEST_P (EntityRenderFailParam, BadCoordThrows)
{
  auto &entity = GetParam ();
  ASSERT_THROW (entity.render (*dummy_renderer, dummy_rect, dummy_len),
                std::logic_error);
}

INSTANTIATE_TEST_SUITE_P (XTooLow, EntityRenderFailParam,
                          testing::Values (Entity (-1, 0, DUMMY_COLOR)));
INSTANTIATE_TEST_SUITE_P (XTooHigh, EntityRenderFailParam,
                          testing::Values (Entity (50, 0, DUMMY_COLOR)));
INSTANTIATE_TEST_SUITE_P (YTooLow, EntityRenderFailParam,
                          testing::Values (Entity (0, -1, DUMMY_COLOR)));
INSTANTIATE_TEST_SUITE_P (YTooHigh, EntityRenderFailParam,
                          testing::Values (Entity (0, 50, DUMMY_COLOR)));
