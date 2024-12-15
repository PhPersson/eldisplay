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
        #updateBtn {
            background-color: #ffc107;
        }
        #updateBtn:hover {
            background-color: #e0a800;
        }
        button {
            display: flex;
            align-items: center;
            justify-content: center;
            background-color: #17a2b8;
            color: white;
            border: none;
            cursor: pointer;
        }
        button:hover {
            background-color: #138496;
        }
        button .material-icons {
            margin-right: 5px;
        }
        .status {
            text-align: center;
            margin-top: 10px;
            font-size: 14px;
            color: #777;
        }

        /* Tooltip styles */
        .tooltip {
            position: relative;
            cursor: pointer;
        }

        .tooltip .tooltiptext {
            visibility: hidden;
            width: 200px;
            background-color: #333;
            color: #fff;
            text-align: center;
            padding: 5px 10px;
            border-radius: 5px;
            position: absolute;
            z-index: 1;
            bottom: 125%; /* Position above the label */
            left: 50%;
            transform: translateX(-50%);
            opacity: 0;
            transition: opacity 0.3s;
        }

        .tooltip .tooltiptext::after {
            content: '';
            position: absolute;
            top: 100%; /* Bottom of the tooltip */
            left: 50%;
            transform: translateX(-50%);
            border-width: 5px;
            border-style: solid;
            border-color: #333 transparent transparent transparent;
        }

        .tooltip:hover .tooltiptext {
            visibility: visible;
            opacity: 1;
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

    <div class="tooltip">
        <label for="tax">
            <input type="checkbox" id="tax" name="tax" {{tax}}> Räkna in extra avgifter
        </label>
        <span class="tooltiptext">Aktivera om du vill räkna med 25% skatt + 0.53.5 öre/kWh (energiskatt)</span>
    </div>

    <div class="tooltip">
        <label for="nightMode">
            <input type="checkbox" id="nightMode" name="nightMode" {{nightMode}}> Aktivera nattläge
        </label>
        <span class="tooltiptext">Stänger av skärmen mellan 23:00 och 06:00.</span>
    </div>

 <div class="tooltip">
        <label for="tax">
                <input type="submit" value="Spara">
        </label>
        <span class="tooltiptext">Sparar och startar om enheten</span>
    </div>


    <div class="tooltip">
        <button id="updateBtn" type="button" onclick="location.href='/update'">Uppdatera</button>
        <span class="tooltiptext">Klicka för att uppdatera enheten med ny mjukvara.</span>
    </div>
    
    <button type="button" id="toggleDisplayBtn">Skärm av/på</button>
</form>


<script>
    document.getElementById('toggleDisplayBtn').addEventListener('click', function() {
        fetch('/toggleDisplay', { method: 'POST' })
    });
</script>

</body>
</html>

)rawliteral";

#endif