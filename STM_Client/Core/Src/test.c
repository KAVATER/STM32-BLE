case HCI_LE_ADVERTISING_REPORT_SUBEVT_CODE:
{
  uint8_t *adv_report_data;
  /* USER CODE BEGIN EVT_LE_ADVERTISING_REPORT */
  char    local_name[32] = {0};   /* buffer to hold the decoded device name  */
  uint8_t name_len = 0;           /* how many name bytes we actually got     */
  /* USER CODE END EVT_LE_ADVERTISING_REPORT */
  le_advertising_event = (hci_le_advertising_report_event_rp0 *) meta_evt->data;

  event_type = le_advertising_event->Advertising_Report[0].Event_Type;
  event_data_size = le_advertising_event->Advertising_Report[0].Length_Data;

  adv_report_data = (uint8_t*)(&le_advertising_event->Advertising_Report[0].Length_Data) + 1;
  k = 0;

  if (event_type == ADV_IND)
  {
    while(k < event_data_size)
    {
      adlength = adv_report_data[k];
      adtype   = adv_report_data[k + 1];
      switch (adtype)
      {
        case AD_TYPE_FLAGS:
          break;

        case AD_TYPE_TX_POWER_LEVEL:
          break;

        case AD_TYPE_MANUFACTURER_SPECIFIC_DATA:
          /* ... keep the existing ST P2P server filter code here unchanged ... */
          if (adlength >= 7 && adv_report_data[k + 2] == 0x01)
          {
            /* existing CFG_DEV_ID_P2P_SERVER1 handling stays as-is */
          }
          break;

        case AD_TYPE_SERVICE_DATA:
          break;

        /* USER CODE BEGIN adtype_default */
        case AD_TYPE_COMPLETE_LOCAL_NAME:   /* 0x09 */
        case AD_TYPE_SHORTENED_LOCAL_NAME:  /* 0x08 */
          name_len = adlength - 1;                      /* -1 strips the type byte */
          if (name_len > sizeof(local_name) - 1)
            name_len = sizeof(local_name) - 1;          /* never overflow buffer   */
          memcpy(local_name, &adv_report_data[k + 2], name_len);
          local_name[name_len] = '\0';
          break;
        /* USER CODE END adtype_default */

        default:
          break;
      }
      k += adlength + 1;
    } /* end while */

    /* USER CODE BEGIN EVT_LE_ADVERTISING_REPORT_2 */
    printf("%02X:%02X:%02X:%02X:%02X:%02X | RSSI %4d dBm | %s\r\n",
           le_advertising_event->Advertising_Report[0].Address[5],
           le_advertising_event->Advertising_Report[0].Address[4],
           le_advertising_event->Advertising_Report[0].Address[3],
           le_advertising_event->Advertising_Report[0].Address[2],
           le_advertising_event->Advertising_Report[0].Address[1],
           le_advertising_event->Advertising_Report[0].Address[0],
           (int8_t)*(uint8_t*)(adv_report_data + event_data_size),  /* see note below */
           (name_len ? local_name : "(no name)"));
    /* USER CODE END EVT_LE_ADVERTISING_REPORT_2 */
  }
}
break;
