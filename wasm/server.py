#!/usr/bin/env python

from http import server

class MRHTTPRequestHandler(server.SimpleHTTPRequestHandler):
    def end_headers(self):
        self.send_my_headers()

        server.SimpleHTTPRequestHandler.end_headers(self)

    def send_my_headers(self):
        self.send_header("Cross-Origin-Embedder-Policy", "require-corp")
        self.send_header("Cross-Origin-Opener-Policy", "same-origin")

if __name__ == '__main__':
    server.test(HandlerClass=MRHTTPRequestHandler, port=9310)
