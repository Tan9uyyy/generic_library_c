#define T_IMPL_DEQUE
#define T_QUEUE_TAG int_queue
#define queue_datum_t int

#define DESTRUCTOR(val) NULL
#define DESTRUCTOR_IS_NULL // macro flag pour indiquer que le destructeur est
                           // NULL (ça me simplifie pour les if parce que sinon
                           // je comprends rien)
#define COMPARATOR(val1, val2) ((val1) == (val2))
#define PRINTER(val) printf("%d", (val))

#include <libellul.h>
#include <libellul/type/queue.h>

void queue_NULL(void) {
  test_suite("NULL as a queue");

  int_queue_t queue = int_queue_new();

  test_assert(int_queue_is_empty(queue), "NULL is an empty queue");
  test_assert(int_queue_length(queue) == 0, "NULL length is 0");

  int_queue_print(queue);

  int_queue_delete(queue);
  test_assert(1, "Can delete NULL as a queue");
}

void queue_test(void) {
  int_queue_t queue = int_queue_new();
  int input = 42;
  int output = 0;

  int inputs[7] = {1, 2, 3, -1, -2, 0, 87};
  int outputs[7] = {0, 0, 0, 0, 0, 0, 0};

  test_suite("Queue push one element");

  queue = int_queue_push(input, queue);

  int_queue_print(queue);

  test_assert(!int_queue_is_empty(queue), "Queue is not empty after push");
  test_assert(int_queue_length(queue) == 1, "Queue length is 1");

  test_assert(int_queue_first(queue) == input, "Correct push");

  test_suite("Queue pop one element");

  queue = int_queue_pop(&output, queue);

  int_queue_print(queue);

  test_assert(output == input, "Correct pop");

  test_assert(int_queue_is_empty(queue), "Queue is empty after fully popped");

  test_suite("Queue push multiple elements");

  for (int i = 0; i < 7; i++) {
    queue = int_queue_push(inputs[i], queue);
    int_queue_print(queue);

    test_assert(int_queue_first(queue) == inputs[0],
                "First value is the first value pushed");
  }

  test_assert(int_queue_length(queue) == 7, "Queue length is 7");

  test_suite("Queue pop multiple elements");

  for (int i = 0; i < 7; i++) {
    queue = int_queue_pop(&outputs[i], queue);
    int_queue_print(queue);

    test_assert(outputs[i] == inputs[i], "Popped value is correct");
  }

  test_assert(int_queue_is_empty(queue), "Queue is empty after fully popped");

  test_suite("Queue delete");

  for (int i = 0; i < 7; i++) {
    queue = int_queue_push(inputs[i], queue);
  }

  int_queue_delete(queue);

  test_assert(1, "Queue is deleted");
}

int main(int argc, char *argv[]) {
  unit_test(argc, argv);

  test_suite(
      "\n\n\n ================================================ TEST 03-queue.c "
      "=========================================================");

  queue_NULL();
  queue_test();

  exit(EXIT_SUCCESS);
}