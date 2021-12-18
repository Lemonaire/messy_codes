from PyPDF2 import PdfFileReader, PdfFileWriter
import os,re

pattern = r'.*.pdf'     # 需要合成的 pdf pattern
work_dir = r'D:\test'   # 目标路径
merge_file_path = './merge_file.pdf'    # 合成的文件路径

# 获取某目录下的所有文件（含子文件夹中的文件）
def findAllFile(path):
    for cur_dir, dirs, files in os.walk(path):
        for file in files:
            if re.match(pattern, file):
                abs_path = os.path.join(cur_dir, file)
                yield abs_path

def main():
    os.chdir(work_dir)
    pdf_writer = PdfFileWriter()
    path = os.getcwd()

    for file in findAllFile(path):
        pdf_reader = PdfFileReader(file)
        for page in range(pdf_reader.getNumPages()):
            pdf_writer.addPage(pdf_reader.getPage(page))

    with open(merge_file_path, 'wb') as output:
        pdf_writer.write(output)

if __name__ == '__main__':
    main()
