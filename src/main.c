#include <stdlib.h>
#include "manager.h"

// -----------------------------------------------------------------------------
// MAIN CODE
// -----------------------------------------------------------------------------
int main(void) {
     systemInit();
     systemProcess();
     systemShutDown();
     return EXIT_SUCCESS;
}
