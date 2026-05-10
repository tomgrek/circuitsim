import base64
import os

files = ['analog.cm', 'digital.cm', 'spice2poly.cm', 'table.cm', 'tlines.cm', 'xtradev.cm', 'xtraevt.cm', 'spinit']
out = "export const models = {\n"

for f in files:
    with open('codemodels/' + f, 'rb') as fp:
        data = fp.read()
    b64 = base64.b64encode(data).decode('utf-8')
    key = f.replace('.', '_')
    out += f"  '{key}': '{b64}',\n"

out += "};\n"
with open('models.ts', 'w') as fp:
    fp.write(out)
