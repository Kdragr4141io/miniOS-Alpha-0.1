import http.server
import socketserver
import webbrowser

PORT = 8000

html_content = """
<!DOCTYPE html>
<html lang="tr">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Açık Kaynak Not Defteri</title>
  <style>
    body {
      font-family: Arial, sans-serif;
      background: #f7f7f7;
      text-align: center;
      padding: 20px;
    }
    h1 { color: #333; }
    .input-area { margin-bottom: 20px; }
    textarea {
      width: 80%;
      height: 80px;
      padding: 10px;
      font-size: 14px;
    }
    button {
      padding: 10px 20px;
      margin-top: 10px;
      cursor: pointer;
      background: #007bff;
      color: white;
      border: none;
      border-radius: 6px;
    }
    ul { list-style: none; padding: 0; }
    li {
      background: white;
      margin: 10px auto;
      padding: 10px;
      border-radius: 6px;
      width: 80%;
      display: flex;
      justify-content: space-between;
      align-items: center;
    }
  </style>
</head>
<body>
  <h1>📝 Not Defteri</h1>
  
  <div class="input-area">
    <textarea id="noteInput" placeholder="Notunu buraya yaz..."></textarea>
    <br>
    <button onclick="addNote()">Ekle</button>
  </div>

  <ul id="notesList"></ul>

  <script>
    let notes = JSON.parse(localStorage.getItem("notes")) || [];

    function renderNotes() {
      const notesList = document.getElementById("notesList");
      notesList.innerHTML = "";
      notes.forEach((note, index) => {
        const li = document.createElement("li");
        li.innerHTML = `
          <span>${note}</span>
          <button onclick="deleteNote(${index})">❌</button>
        `;
        notesList.appendChild(li);
      });
      localStorage.setItem("notes", JSON.stringify(notes));
    }

    function addNote() {
      const input = document.getElementById("noteInput");
      if (input.value.trim() !== "") {
        notes.push(input.value);
        input.value = "";
        renderNotes();
      }
    }

    function deleteNote(index) {
      notes.splice(index, 1);
      renderNotes();
    }

    renderNotes();
  </script>
</body>
</html>
"""

class Handler(http.server.SimpleHTTPRequestHandler):
    def do_GET(self):
        if self.path == "/" or self.path == "/index.html":
            self.send_response(200)
            self.send_header("Content-type", "text/html; charset=utf-8")
            self.end_headers()
            self.wfile.write(html_content.encode("utf-8"))
        else:
            self.send_error(404, "File Not Found")

with socketserver.TCPServer(("", PORT), Handler) as httpd:
    print(f"Not Defteri çalışıyor → http://localhost:{PORT}")
    webbrowser.open(f"http://localhost:{PORT}")
    httpd.serve_forever()
