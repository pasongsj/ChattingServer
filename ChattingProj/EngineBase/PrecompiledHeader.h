#pragma once

#include <WS2tcpip.h> // inet_pton �Լ��� ����ϱ� ���� ���
#include <WinSock2.h> // window.h���� ������ ���ʿ� �־�� �Ѵ�.
#include <Windows.h>

#pragma comment (lib, "ws2_32") // <= ������ ���� ����� ���� ���̺귯��

#include <memory>
#include <iostream>
#include <cmath>
#include <mutex>

// std
#include <map>
#include <set>
#include <list>
#include <vector>
#include <string>
#include <string_view>
#include <filesystem>
#include <functional>