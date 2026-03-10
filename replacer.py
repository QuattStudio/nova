import os

def should_be_lower(text, start):
    checked = 0
    i = start

    while i < len(text) and checked < 4:
        c = text[i]

        if c == '_':
            i += 1
            continue

        if c.islower():
            return True

        checked += 1
        i += 1

    return False


def process_file(path):
    with open(path, "r", encoding="utf-8") as f:
        content = f.read()

    out = []
    i = 0

    while i < len(content):
        if content[i:i+2] == "SA":
            if should_be_lower(content, i+2):
                out.append("nova")
            else:
                out.append("NOVA")
            i += 2
        else:
            out.append(content[i])
            i += 1

    new_content = "".join(out)

    if new_content != content:
        print("Modified:", path)
        with open(path, "w", encoding="utf-8") as f:
            f.write(new_content)


def walk(root):
    for dirpath, _, files in os.walk(root):
        for f in files:
            if f.endswith(".c") or f.endswith(".h"):
                process_file(os.path.join(dirpath, f))


if __name__ == "__main__":
    walk(".")