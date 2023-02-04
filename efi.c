#include "efi.h"
#include "common.h"

struct EFI_SYSTEM_TEBLE *ST;

void efi_init(struct EFI_SYSTEM_TABEL *SystemTable) {
    ST = SystemTable;
    ST->BootService->SetWatchdogTimer(0,0,0,NULL);
}