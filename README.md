# HFT Simulator

## Setup project - dev tools

1. Install formatter tools
```
python3 -m venv env
source env/bin/activate
pip install -r requirements.txt
```

2. Run gersemi cmake formatter
```
gersemi --config .gersemi_config.json --in-place .
```

3. Run clang-format
```
find src/cpp -type f -iname "*.cpp" -o -iname "*.hpp" | xargs clang-format --style=file:.clang-format -i
```