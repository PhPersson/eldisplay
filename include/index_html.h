#ifndef INDEX_HTML_H
#define INDEX_HTML_H

const char index_html[] = R"rawliteral(
<!DOCTYPE html>
<html lang="sv">
<head>
    <meta charset="UTF-8">
    <title>Inställningar - Eldisplay</title>
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <style>
        body {
            font-family: Arial, sans-serif;
            background-color: #f4f4f9;
            margin: 0;
            padding: 20px;
        }
        form {
            background-color: #fff;
            padding: 20px;
            border-radius: 10px;
            box-shadow: 0 2px 5px rgba(0, 0, 0, 0.1);
            max-width: 400px;
            margin: auto;
        }
        h1 {
            text-align: center;
            color: #333;
        }
        label {
            display: block;
            margin-bottom: 10px;
            font-weight: bold;
            color: #555;
        }
        select,
        input[type='text'],
        input[type='number'],
        input[type='submit'],
        button {
            width: 100%;
            padding: 10px;
            margin-bottom: 20px;
            border-radius: 5px;
            border: 1px solid #ccc;
            box-sizing: border-box;
            font-size: 16px;
        }
        input[type='checkbox'] {
            margin-right: 10px;
        }
        input[type='submit'] {
            background-color: #28a745;
            color: white;
            border: none;
            cursor: pointer;
        }
        input[type='submit']:hover {
            background-color: #218838;
        }
        button {
            background-color: #17a2b8;
            color: white;
            border: none;
            cursor: pointer;
        }
        button:hover {
            background-color: #138496;
        }

        /* Mobile styling */
        @media (max-width: 600px) {
            body {
                padding: 10px;
            }
            form {
                padding: 15px;
            }
            h1 {
                font-size: 1.2em;
            }
            select,
            input[type='text'],
            input[type='number'],
            input[type='submit'],
            button {
                font-size: 1em;
                padding: 8px;
            }
        }
    </style>
</head>
<body>

<h1>Inställningar</h1>

<form action="/config" method="POST">
    <label for="area">Elprisområde:</label>
    <select id="area" name="area" required>
        <option value="SE1" {{area == 'SE1' ? 'selected' : ''}}>SE1</option>
        <option value="SE2" {{area == 'SE2' ? 'selected' : ''}}>SE2</option>
        <option value="SE3" {{area == 'SE3' ? 'selected' : ''}}>SE3</option>
        <option value="SE4" {{area == 'SE4' ? 'selected' : ''}}>SE4</option>
    </select>

    <label for="threshold">Högt elpris:</label>
    <input type="number" id="threshold" name="threshold" step="0.01" value="{{threshold}}" placeholder="Ange när elpriset ska räknas som högt">

    <label for="tax">
        <input type="checkbox" id="tax" name="tax" {{tax}}"> Räkna extra avgifter? (25% skatt + 0.53.5/ kWh)
    </label>

    <input type="submit" value="Spara">
    <button type="button" onclick="location.href='/update'">Uppdatera</button>
</form>



</body>
</html>

)rawliteral";

#endif
