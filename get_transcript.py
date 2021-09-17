from bs4 import BeautifulSoup
import requests

if __name__ == "__main__":
    course_link = "https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-172-performance-engineering-of-software-systems-fall-2018/lecture-videos"
    proxies = {'http':'http://localhost:10809', 'https': 'http://localhost:10809'}
    root = "https://ocw.mit.edu"
    course_page = requests.get(url = course_link, proxies=proxies)
    bs = BeautifulSoup(course_page.text)
    lecture_links = bs.find_all('a', class_ = 'bullet medialink')

    for lecture_link in lecture_links:
        video_link = root + lecture_link.get('href')
        video_page = requests.get(url=video_link, proxies=proxies)
        bs = BeautifulSoup(video_page.text)
        try:
            transcript_link = root + bs.find_all('a', class_ = 'transcript-link')[0].get('href')
            transcript = requests.get(url=transcript_link, proxies=proxies)
            # ':' is not allowed in a file name 
            open(lecture_link.text.replace(":", "") + ".pdf", 'wb').write(transcript.content)
        except IndexError:  # There is no transcript file for Lecture 20
            print("IndexError")
