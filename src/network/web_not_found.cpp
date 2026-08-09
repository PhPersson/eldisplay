#include "web_not_found.h"

const char not_found_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>404</title>
  <style>
    :root {
      --bg: #f5f5f7;
      --card: rgba(255,255,255,0.72);
      --border: rgba(255,255,255,0.6);
      --text: #1d1d1f;
      --muted: #6e6e73;
      --accent: #0071e3;
      --shadow: 0 24px 80px rgba(0,0,0,0.12);
    }
    * { box-sizing: border-box; }
    html, body {
      margin: 0;
      min-height: 100%;
      font-family: -apple-system, BlinkMacSystemFont, "SF Pro Text", "Helvetica Neue", Arial, sans-serif;
      background: radial-gradient(circle at top, #ffffff 0%, #f5f5f7 45%, #ececf0 100%);
      color: var(--text);
    }
    body {
      min-height: 100vh;
      display: grid;
      place-items: center;
      padding: 24px;
    }
    .card {
      width: 100%;
      max-width: 560px;
      background: var(--card);
      backdrop-filter: blur(24px) saturate(180%);
      -webkit-backdrop-filter: blur(24px) saturate(180%);
      border: 1px solid var(--border);
      border-radius: 28px;
      box-shadow: var(--shadow);
      padding: 28px;
      text-align: center;
    }
    .emoji { font-size: 56px; line-height: 1; margin-bottom: 12px; }
    .code {
      display: inline-block;
      font-size: 13px;
      font-weight: 700;
      color: var(--accent);
      background: rgba(0,113,227,0.10);
      border-radius: 999px;
      padding: 8px 12px;
      margin-bottom: 16px;
    }
    h1 {
      margin: 0 0 10px;
      font-size: 34px;
      line-height: 1.05;
      letter-spacing: -0.04em;
    }
    p {
      margin: 0 auto 10px;
      max-width: 34ch;
      color: var(--muted);
      font-size: 16px;
      line-height: 1.5;
    }
    .path {
      margin: 18px 0 24px;
      padding: 12px 14px;
      border-radius: 16px;
      background: rgba(255,255,255,0.62);
      border: 1px solid rgba(0,0,0,0.06);
      font-family: ui-monospace, SFMono-Regular, Menlo, monospace;
      font-size: 13px;
      overflow-wrap: anywhere;
    }
    .actions {
      display: flex;
      gap: 12px;
      justify-content: center;
      flex-wrap: wrap;
      margin-top: 6px;
    }
    a {
      text-decoration: none;
      border-radius: 999px;
      padding: 12px 18px;
      font-size: 15px;
      font-weight: 600;
    }
    .primary {
      background: var(--accent);
      color: white;
      box-shadow: 0 10px 24px rgba(0,113,227,0.22);
    }
    .secondary {
      background: rgba(255,255,255,0.7);
      color: var(--text);
      border: 1px solid rgba(0,0,0,0.07);
    }
    .footer {
      margin-top: 18px;
      color: var(--muted);
      font-size: 12px;
    }
  </style>
</head>
<body>
  <main class="card">
    <div class="code">Error 404</div>
    <p>The spot price was high, so this page could not be find,</p>
    <div class="actions">
      <a class="primary" href="/">Go home</a>
    </div>
  </main>
</body>
</html>
)rawliteral";