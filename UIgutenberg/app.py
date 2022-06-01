from flask import Flask 
from flask import render_template

app = Flask(__name__)

@app.route('/')
@app.route('/index')
def index():

    return render_template('index.html', Page_title='UI Gutenberg', Grand_title='Click below to access the ebook')
