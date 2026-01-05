# HelloGTK
Exemplos extraídos do [getting started](https://docs.gtk.org/gtk4/getting_started.html) do GTK-4.0.

## Compilando
Para a compilação dos exemplos, basta seguir os comandos a seguir.

```powershell
$ gcc <C_FILE> -o build/<OPERATING_SYSTEM>/<OUTPUT_FILE> $(pkg-config --cflags --libs gtk4)
```

Junto  ao projeto, já foram incluídos os executáveis, compilados utilizando `gcc 13.3.0 Ubuntu`.