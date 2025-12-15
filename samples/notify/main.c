/* Copyright (C) 2025 LightningMods

This program is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 3, or (at your option) any
later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; see the file COPYING. If not, see
<http://www.gnu.org/licenses/>.  */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>


#define SCE_NOTIFICATION_LOCAL_USER_ID_SYSTEM 0xFE


int sceNotificationSend(int userId, bool isLogged, const char* payload);


static const char toast_tmpl[] =
  "{\n"
  "  \"rawData\": {\n"
  "    \"viewTemplateType\": \"InteractiveToastTemplateB\",\n"
  "    \"channelType\": \"Downloads\",\n"
  "    \"useCaseId\": \"IDC\",\n"
  "    \"toastOverwriteType\": \"No\",\n"
  "    \"isImmediate\": true,\n"
  "    \"priority\": 100,\n"
  "    \"viewData\": {\n"
  "      \"icon\": {\n"
  "        \"type\": \"Url\",\n"
  "        \"parameters\": {\n"
  "          \"url\": \"/path/to/icon.png\"\n"
  "        }\n"
  "      },\n"
  "      \"message\": {\n"
  "        \"body\": \"Hello World!\"\n"
  "      },\n"
  "      \"subMessage\": {\n"
  "        \"body\": \"notify sample\"\n"
  "      },\n"
  "      \"actions\": [\n"
  "        {\n"
  "          \"actionName\": \"Go to debug settings\",\n"
  "          \"actionType\": \"DeepLink\",\n"
  "          \"defaultFocus\": true,\n"
  "          \"parameters\": {\n"
  "            \"actionUrl\": \"pssettings:play?function=debug_settings\"\n"
  "          }\n"
  "        }\n"
  "      ]\n"
  "    },\n"
  "    \"platformViews\": {\n"
  "      \"previewDisabled\": {\n"
  "        \"viewData\": {\n"
  "          \"icon\": {\n"
  "            \"type\": \"Predefined\",\n"
  "            \"parameters\": {\n"
  "              \"icon\": \"download\"\n"
  "            }\n"
  "          },\n"
  "          \"message\": {\n"
  "            \"body\": \"notify sample is running\"\n"
  "          }\n"
  "        }\n"
  "      }\n"
  "    }\n"
  "  },\n"
  "  \"createdDateTime\": \"2025-12-14T03:14:51.473Z\",\n"
  "  \"localNotificationId\": \"588193127\"\n"
  "}";


int
main(void) {
  return sceNotificationSend(SCE_NOTIFICATION_LOCAL_USER_ID_SYSTEM,
			     true, toast_tmpl);
}

