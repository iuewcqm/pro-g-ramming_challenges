#!/usr/bin/env python3

def generateVigenereTable():
    alphabet = 'abcdefghijklmnopqrstuvwxyz'
    return [alphabet[i:]+alphabet[:i] for i in range(len(alphabet))]

def encrypt(message, key):
    table = generateVigenereTable()
    return ''.join([table[ord(m)-ord('a')][ord(k)-ord('a')] for m,k in zip(message, key)])

def decrypt(encrypted, key):
    table = generateVigenereTable()
    return ''.join([table[0][table[ord(k)-ord('a')].index(e)] for e,k in zip(encrypted, key)])

def decryptChar(encrypted, decrypted):
    table = generateVigenereTable()
    alphabet = [table[ord(ch)-ord('a')][ord(ch)-ord('a')] for ch in table[0]]
    for i in range(len(alphabet)//2):
        if len(decrypted) < len(encrypted) and alphabet[i] == encrypted[len(decrypted)]:
            yield from decryptChar(encrypted, decrypted + table[0][i])
            yield from decryptChar(encrypted, decrypted + table[0][i+len(alphabet)//2])
    if len(encrypted) == len(decrypted):
        yield decrypted

def tryDecryptMessage(encrypt):
    decryptedMessagesGenerator = decryptChar(encrypt, '')
    decryptedMessages = []
    for message in decryptedMessagesGenerator:
        decryptedMessages.append(message)
    return decryptedMessages

def menu():
    print("1: encrypt\n2: decrypt\n3: try decrypt without key\n4: exit")
    choice = input()
    if choice == '1':
        message = input('message: ')
        key = input('key: ')
        print(encrypt(message, key))
    elif choice == '2':
        encrypted = input('encrypted message: ')
        key = input('key: ')
        print(decrypt(encrypted, key))
    elif choice == '3':
        encrypted = input('encrypted message: ')
        decryptedMessages = tryDecryptMessage(encrypted)
        for message in decryptedMessages:
            print(message)
    
if __name__ == '__main__':
    menu()
