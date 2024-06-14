import struct

# Leer el archivo binario
with open('rgb565data.bin', 'rb') as f:
    data = f.read()

# Verificar el tamaño del archivo
expected_size = 240 * 240 * 2  # 240x240 píxeles con 2 bytes por píxel en RGB565
if len(data) != expected_size:
    print(f"El tamaño del archivo no coincide con lo esperado: {len(data)} bytes, se esperaban {expected_size} bytes.")
    exit(1)

# Convertir los datos a una lista de enteros en formato RGB565
rgb565_data = struct.unpack('<' + 'H' * (len(data) // 2), data)

# Formatear los datos en un array compatible con Arduino
formatted_data = []
for i in range(240):
    row = rgb565_data[i * 240:(i + 1) * 240]
    formatted_row = ', '.join(f'0x{pixel:04X}' for pixel in row)
    formatted_data.append(f'{{ {formatted_row} }}')

# Guardar el array en un archivo .h
with open('rick_astley_image_rgb565.h', 'w') as f:
    f.write('#define IMAGE_WIDTH 240\n')
    f.write('#define IMAGE_HEIGHT 240\n')
    f.write('const uint16_t rickAstleyImage[IMAGE_WIDTH][IMAGE_HEIGHT] PROGMEM = {\n')
    f.write(',\n'.join(formatted_data))
    f.write('\n};')

print("Conversión completada y guardada en rick_astley_image_rgb565.h")
