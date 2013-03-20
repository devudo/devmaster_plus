Aegir HipChat Integration
=========================

Send task status messages from Aegir to a HipChat room.

Requirements
------------

1. HipChat [API token](https://www.hipchat.com/admin/api).

2. HipChat room id.

    To get a list of rooms, [use the API](https://api.hipchat.com/v1/rooms/list?auth_token=<token>)
    (replace <token> with your API token).

3. A working Aegir installation.

Installation
------------

1. Upload the module to sites/{example.com}/modules and enable the module.

2. Login to Aegir and browser to example.com/admin/hosting/hipchat

    You need the "Administer Hosting Settings" permission to access this page.

3. Add your API token and room id.

4. Select which task actions you want notifications for.
