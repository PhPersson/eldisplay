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
  <div class="shell">
    <div class="card">
      <h2>Elpris</h2>

      <form action="/save" method="get">
        <div class="field">
          <label for="area">Price area</label>
          <select id="area" name="area">
            <option value="SE1">SE1</option>
            <option value="SE2">SE2</option>
            <option value="SE3">SE3</option>
            <option value="SE4">SE4</option>
          </select>
        </div>

        <div class="toggle">
          <div class="toggle-text">
            <strong>Add tax</strong>
            <span>Include tax in the shown price.</span>
          </div>
          <input type="checkbox" name="tax" value="1">
        </div>

        <div class="field">
          <label for="threshold">Threshold</label>
          <input id="threshold" type="number" step="0.01" name="threshold">
        </div>

        <button type="submit">Save changes</button>
      </form>
    </div>
  </div>
</body>
<style>
  :root {
    --bg: #f5f5f7;
    --card: rgba(255, 255, 255, 0.72);
    --card-border: rgba(255, 255, 255, 0.55);
    --text: #1d1d1f;
    --muted: #6e6e73;
    --accent: #0071e3;
    --accent-hover: #0077ed;
    --input-bg: rgba(255, 255, 255, 0.82);
    --shadow: 0 20px 60px rgba(0, 0, 0, 0.10);
    --radius: 24px;
  }

  * {
    box-sizing: border-box;
  }

  html, body {
    margin: 0;
    padding: 0;
    font-family: -apple-system, BlinkMacSystemFont, "SF Pro Text", "Helvetica Neue", Arial, sans-serif;
    background:
      radial-gradient(circle at top, #ffffff 0%, #f5f5f7 45%, #ececf0 100%);
    color: var(--text);
    min-height: 100%;
  }

  body {
    min-height: 100vh;
    display: flex;
    align-items: center;
    justify-content: center;
    padding: 24px;
  }

  .shell {
    width: 100%;
    max-width: 460px;
  }

  .card {
    background: var(--card);
    backdrop-filter: blur(24px) saturate(180%);
    -webkit-backdrop-filter: blur(24px) saturate(180%);
    border: 1px solid var(--card-border);
    border-radius: var(--radius);
    box-shadow: var(--shadow);
    padding: 28px;
  }

  h2 {
    margin: 0 0 6px;
    font-size: 28px;
    font-weight: 700;
    letter-spacing: -0.03em;
  }

  .sub {
    margin: 0 0 24px;
    color: var(--muted);
    font-size: 15px;
    line-height: 1.45;
  }

  .field {
    margin-top: 18px;
  }

  label {
    display: block;
    margin-bottom: 8px;
    color: var(--muted);
    font-size: 13px;
    font-weight: 600;
    letter-spacing: -0.01em;
  }

  select,
  input[type="number"] {
    width: 100%;
    border: 1px solid rgba(0, 0, 0, 0.08);
    background: var(--input-bg);
    color: var(--text);
    border-radius: 16px;
    padding: 14px 16px;
    font-size: 16px;
    outline: none;
    appearance: none;
    -webkit-appearance: none;
    transition: border-color 160ms ease, box-shadow 160ms ease, background 160ms ease;
    box-shadow: inset 0 1px 0 rgba(255,255,255,0.65);
  }

  select:focus,
  input[type="number"]:focus {
    border-color: rgba(0, 113, 227, 0.45);
    box-shadow: 0 0 0 4px rgba(0, 113, 227, 0.12);
    background: #fff;
  }

  .toggle {
    margin-top: 18px;
    display: flex;
    align-items: center;
    justify-content: space-between;
    gap: 16px;
    padding: 14px 16px;
    border-radius: 18px;
    background: rgba(255,255,255,0.58);
    border: 1px solid rgba(0,0,0,0.06);
  }

  .toggle-text {
    display: flex;
    flex-direction: column;
    gap: 2px;
  }

  .toggle-text strong {
    font-size: 15px;
    font-weight: 600;
    letter-spacing: -0.01em;
  }

  .toggle-text span {
    font-size: 13px;
    color: var(--muted);
  }

  input[type="checkbox"] {
    width: 44px;
    height: 28px;
    appearance: none;
    -webkit-appearance: none;
    background: #d2d2d7;
    border-radius: 999px;
    position: relative;
    cursor: pointer;
    transition: background 180ms ease;
    flex: 0 0 auto;
  }

  input[type="checkbox"]::after {
    content: "";
    position: absolute;
    top: 3px;
    left: 3px;
    width: 22px;
    height: 22px;
    border-radius: 50%;
    background: white;
    box-shadow: 0 1px 4px rgba(0,0,0,0.18);
    transition: transform 180ms ease;
  }

  input[type="checkbox"]:checked {
    background: var(--accent);
  }

  input[type="checkbox"]:checked::after {
    transform: translateX(16px);
  }

  button {
    width: 100%;
    margin-top: 24px;
    border: 0;
    border-radius: 999px;
    padding: 14px 18px;
    background: var(--accent);
    color: white;
    font-size: 16px;
    font-weight: 600;
    letter-spacing: -0.01em;
    cursor: pointer;
    transition: transform 140ms ease, background 140ms ease, box-shadow 140ms ease;
    box-shadow: 0 10px 24px rgba(0, 113, 227, 0.22);
  }

  button:hover {
    background: var(--accent-hover);
  }

  button:active {
    transform: scale(0.985);
  }

  .foot {
    margin-top: 14px;
    text-align: center;
    color: var(--muted);
    font-size: 12px;
  }

  @media (max-width: 480px) {
    .card {
      padding: 22px;
      border-radius: 22px;
    }

    h2 {
      font-size: 24px;
    }
  }
</style>
</html>
)rawliteral";