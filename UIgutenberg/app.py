from flask import Flask 
from flask import render_template
from urllib.request import urlopen
from bs4 import BeautifulSoup

app = Flask(__name__)

@app.route('/')
@app.route('/index')
def index():

    

    

    with urlopen("https://gutenberg.org/files/2701/2701-h/2701-h.htm") as response:
        body = response.read()

    # Parse the html file
    soup = BeautifulSoup(body, 'html.parser')

    # Format the parsed html file
    strhtm = soup.getText()




    return render_template('index.html', Page_title='UIGutenberg', Book_title=strhtm, code=body)
