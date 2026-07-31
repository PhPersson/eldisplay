#include "webui.h"

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    body { font-family: Arial, sans-serif; max-width: 420px; margin: 40px auto; padding: 16px; }
    label { display:block; margin-top: 16px; }
    select, input[type=number] { width: 100%; padding: 10px; font-size: 16px; }
    button { margin-top: 20px; padding: 12px 16px; font-size: 16px; width: 100%; }
  </style>
</head>
<body>
  <h2>Elpris Settings</h2>
  <form action="/save" method="get">
    <label>Price area</label>
    <select name="area">
      <option value="SE1">SE1</option>
      <option value="SE2">SE2</option>
      <option value="SE3">SE3</option>
      <option value="SE4">SE4</option>
    </select>

    <label>
      <input type="checkbox" name="tax" value="1">
      Add tax
    </label>

    <label>Threshold</label>
    <input type="number" step="0.01" name="threshold">

    <button type="submit">Save</button>
  </form>
</body>
</html>
)rawliteral";