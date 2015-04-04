#include "app.h"

void app_run(void) {
    typedef void (*app_ptr_t)(void) __attribute__ ((noreturn));
    app_ptr_t app_start = (app_ptr_t)0;
    app_start();
}

