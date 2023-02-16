from aip import AipOcr
import json

""" 你的 APPID AK SK """
APP_ID = '24057924'
API_KEY = 'Yrj7dIv17nHQ9hy23KZ1XWTT'
SECRET_KEY = 'iEK567uchrXyrTeFZCj7wHhsO8f1rucu'

client = AipOcr(APP_ID, API_KEY, SECRET_KEY)

""" 读取图片 """
def get_file_content(filePath):
    with open(filePath, 'rb') as fp:
        return fp.read()


image = get_file_content('1.png')

""" 调用通用文字识别, 图片参数为本地图片 """
client.basicGeneral(image)

""" 如果有可选参数 """
options = {}
"""检测语言类型"""
options["language_type"] = "CHN_ENG"
"""检测图片朝向"""
options["detect_direction"] = "true"
"""检测语言"""
options["detect_language"] = "true"
"""置信度"""
options["probability"] = "true"

""" 带参数调用通用文字识别, 图片参数为本地图片 """
result = client.basicGeneral(image, options)
print(result)
# 字典类型数据
# print(type(result))
# 输出识别文字
for i in result["words_result"]:
    print(i["words"])
    # str类型
    # print(type(i["words"]))

"""
# sort_keys 如果是字典对象，选择True的话，会按照键的ASCII码来排序 
# indent缩进
# separators 对象分隔符，默认为, 
# ensure_ascii：默认值True，如果dict内含有non-ASCII的字符，
# 则会类似\\uXXXX的显示数据，设置成False后，就能正常显示
"""
# 结果对齐，格式化
print(json.dumps(result, sort_keys=True, indent=4, separators=(',', ': '), ensure_ascii=False))
