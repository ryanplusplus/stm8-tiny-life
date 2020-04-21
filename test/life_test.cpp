/*!
 * @file
 * @brief
 */

extern "C" {
#include "life.h"
}

#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

enum {
  GridSize = 8
};

#define b(_0, _1, _2, _3, _4, _5, _6, _7) \
  ((uint8_t)((_7 << 7) | (_6 << 6) | (_5 << 5) | (_4 << 4) | (_3 << 3) | (_2 << 2) | (_1 << 1) | _0))

TEST_GROUP(life) {
  life_t self;

  void setup() {
    life_init(&self);
  }

  void should_transition(const uint8_t* initial, const uint8_t* expected) {
    life_seed(&self, initial);
    life_step(&self);

    const uint8_t* actual = life_state(&self);

    MEMCMP_EQUAL(expected, actual, GridSize);
  }
};

TEST(life, should_not_create_something_from_nothing) {
  uint8_t initial[8] = {
    b(0, 0, 0, 0, 0, 0, 0, 0),
    b(0, 0, 0, 0, 0, 0, 0, 0),
    b(0, 0, 0, 0, 0, 0, 0, 0),
    b(0, 0, 0, 0, 0, 0, 0, 0),
    b(0, 0, 0, 0, 0, 0, 0, 0),
    b(0, 0, 0, 0, 0, 0, 0, 0),
    b(0, 0, 0, 0, 0, 0, 0, 0),
    b(0, 0, 0, 0, 0, 0, 0, 0)
  };

  uint8_t expected[8] = {
    b(0, 0, 0, 0, 0, 0, 0, 0),
    b(0, 0, 0, 0, 0, 0, 0, 0),
    b(0, 0, 0, 0, 0, 0, 0, 0),
    b(0, 0, 0, 0, 0, 0, 0, 0),
    b(0, 0, 0, 0, 0, 0, 0, 0),
    b(0, 0, 0, 0, 0, 0, 0, 0),
    b(0, 0, 0, 0, 0, 0, 0, 0),
    b(0, 0, 0, 0, 0, 0, 0, 0)
  };

  should_transition(initial, expected);
}

TEST(life, live_cells_with_fewer_than_two_neighbors_should_die) {
  uint8_t initial[8] = {
    b(0, 0, 0, 0, 1, 0, 0, 0),
    b(0, 0, 1, 0, 0, 1, 0, 0),
    b(0, 0, 0, 0, 0, 0, 0, 0),
    b(0, 0, 0, 0, 0, 0, 0, 0),
    b(0, 0, 0, 0, 1, 1, 0, 0),
    b(0, 1, 0, 0, 0, 0, 0, 0),
    b(0, 1, 0, 0, 0, 0, 0, 1),
    b(0, 0, 0, 0, 0, 0, 1, 0)
  };

  uint8_t expected[8] = {
    b(0, 0, 0, 0, 0, 0, 0, 0),
    b(0, 0, 0, 0, 0, 0, 0, 0),
    b(0, 0, 0, 0, 0, 0, 0, 0),
    b(0, 0, 0, 0, 0, 0, 0, 0),
    b(0, 0, 0, 0, 0, 0, 0, 0),
    b(0, 0, 0, 0, 0, 0, 0, 0),
    b(0, 0, 0, 0, 0, 0, 0, 0),
    b(0, 0, 0, 0, 0, 0, 0, 0)
  };

  should_transition(initial, expected);
}

TEST(life, live_cells_with_two_or_three_neighbors_should_live) {
  uint8_t initial[8] = {
    b(0, 0, 0, 0, 0, 0, 0, 0),
    b(0, 1, 1, 0, 0, 0, 0, 0),
    b(0, 1, 0, 0, 0, 1, 1, 0),
    b(0, 0, 0, 0, 0, 1, 1, 0),
    b(0, 0, 0, 0, 0, 0, 0, 0),
    b(0, 0, 0, 0, 0, 0, 0, 0),
    b(0, 0, 0, 0, 0, 0, 1, 0),
    b(0, 0, 0, 0, 0, 1, 1, 0)
  };

  uint8_t expected[8] = {
    b(0, 0, 0, 0, 0, 0, 0, 0),
    b(0, 1, 1, 0, 0, 0, 0, 0),
    b(0, 1, 1, 0, 0, 1, 1, 0),
    b(0, 0, 0, 0, 0, 1, 1, 0),
    b(0, 0, 0, 0, 0, 0, 0, 0),
    b(0, 0, 0, 0, 0, 0, 0, 0),
    b(0, 0, 0, 0, 0, 1, 1, 0),
    b(0, 0, 0, 0, 0, 1, 1, 0)
  };

  should_transition(initial, expected);
}

TEST(life, dead_cells_with_three_neighbors_should_become_alive) {
  uint8_t initial[8] = {
    b(0, 0, 0, 0, 0, 0, 0, 0),
    b(0, 0, 1, 1, 0, 0, 1, 1),
    b(0, 0, 0, 0, 0, 0, 1, 0),
    b(0, 0, 0, 1, 0, 0, 0, 0),
    b(0, 0, 0, 0, 0, 0, 0, 0),
    b(0, 0, 0, 0, 0, 0, 0, 0),
    b(0, 0, 0, 0, 0, 0, 0, 0),
    b(0, 0, 0, 0, 0, 0, 0, 0)
  };

  uint8_t expected[8] = {
    b(0, 0, 0, 0, 0, 0, 0, 0),
    b(0, 0, 0, 0, 0, 0, 1, 1),
    b(0, 0, 1, 1, 0, 0, 1, 1),
    b(0, 0, 0, 0, 0, 0, 0, 0),
    b(0, 0, 0, 0, 0, 0, 0, 0),
    b(0, 0, 0, 0, 0, 0, 0, 0),
    b(0, 0, 0, 0, 0, 0, 0, 0),
    b(0, 0, 0, 0, 0, 0, 0, 0)
  };

  should_transition(initial, expected);
}

TEST(life, should_apply_all_rules_together) {
  uint8_t initial[8] = {
    b(0, 0, 0, 0, 0, 0, 1, 0),
    b(0, 1, 1, 1, 0, 0, 1, 0),
    b(0, 1, 0, 1, 0, 0, 0, 0),
    b(0, 1, 1, 1, 0, 0, 0, 0),
    b(0, 0, 0, 0, 0, 0, 0, 0),
    b(0, 0, 0, 0, 0, 0, 0, 0),
    b(0, 0, 0, 0, 0, 0, 0, 0),
    b(0, 0, 0, 0, 0, 0, 0, 0)
  };

  uint8_t expected[8] = {
    b(0, 0, 1, 0, 0, 0, 0, 0),
    b(0, 1, 0, 1, 0, 0, 0, 0),
    b(1, 0, 0, 0, 1, 0, 0, 0),
    b(0, 1, 0, 1, 0, 0, 0, 0),
    b(0, 0, 1, 0, 0, 0, 0, 0),
    b(0, 0, 0, 0, 0, 0, 0, 0),
    b(0, 0, 0, 0, 0, 0, 0, 0),
    b(0, 0, 0, 0, 0, 0, 0, 0)
  };

  should_transition(initial, expected);
}
