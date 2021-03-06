#pragma once

#include <gsl/gsl>
#include "halley/utils/utils.h"
#include <vector>

namespace Halley {
	class String;
	class Path;

	class FileSystem
	{
	public:
		static bool exists(const Path& p);
		static bool createDir(const Path& p);
		static bool createParentDir(const Path& p);

		static int64_t getLastWriteTime(const Path& p);
		static bool isFile(const Path& p);
		static bool isDirectory(const Path& p);

		static void copyFile(const Path& src, const Path& dst);
		static bool remove(const Path& path);

		static void writeFile(const Path& path, gsl::span<const gsl::byte> data);
		static void writeFile(const Path& path, const Bytes& data);
		static Bytes readFile(const Path& path);

		static std::vector<Path> enumerateDirectory(const Path& path);
		
		static Path getRelative(const Path& path, const Path& parentPath);
		static Path getAbsolute(const Path& path);

		static size_t fileSize(const Path& path);

		static Path getTemporaryPath();

		static int runCommand(const String& command);
	};
}

