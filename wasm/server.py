#!/usr/bin/env python

import os
from http import server


class MRHTTPRequestHandler(server.SimpleHTTPRequestHandler):
    def end_headers(self):
        self.send_my_headers()

        server.SimpleHTTPRequestHandler.end_headers(self)

    def send_my_headers(self):
        self.send_header("Cross-Origin-Embedder-Policy", "require-corp")
        self.send_header("Cross-Origin-Opener-Policy", "same-origin")

if __name__ == '__main__':
    port = 9310

    print(f"Starting server on port {port}...")
    print("Current directory:", os.getcwd())
    print("Directory contents:", os.listdir('.'))

    server.test(HandlerClass=MRHTTPRequestHandler, port=port)
