/* USER CODE BEGIN EVT_LE_ADVERTISING_REPORT */
char local_name[32] = {0};
uint8_t name_len = 0;

/* Table to remember already-seen devices */
static uint8_t seen_devices[10][6];  /* 10 devices, 6 bytes each */
static uint8_t seen_count = 0;
uint8_t already_seen = 0;
/* USER CODE END EVT_LE_ADVERTISING_REPORT */

/* USER CODE BEGIN EVT_LE_ADVERTISING_REPORT_2 */
/* Check if we've seen this address before */
for (uint8_t i = 0; i < seen_count; i++)
{
    if (memcmp(seen_devices[i],
               le_advertising_event->Advertising_Report[0].Address, 6) == 0)
    {
        already_seen = 1;
        break;
    }
}

/* Only print if it's new */
if (!already_seen && seen_count < 10)
{
    /* Remember this device */
    memcpy(seen_devices[seen_count],
           le_advertising_event->Advertising_Report[0].Address, 6);
    seen_count++;

    /* Now print */
    printf("%02X:%02X:%02X:%02X:%02X:%02X | RSSI %4d dBm | %s\r\n", ...);
}
/* USER CODE END EVT_LE_ADVERTISING_REPORT_2 */
