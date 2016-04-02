/*****************************************************************\
__
/ /
/ /                     __  __
/ /______    _______    / / / / ________   __       __
/ ______  \  /_____  \  / / / / / _____  | / /      / /
/ /      | / _______| / / / / / / /____/ / / /      / /
/ /      / / / _____  / / / / / / _______/ / /      / /
/ /      / / / /____/ / / / / / / |______  / |______/ /
/_/      /_/ |________/ / / / /  \_______/  \_______  /
/_/ /_/                     / /
/ /
High Level Game Framework            /_/

---------------------------------------------------------------

Copyright (c) 2007-2011 - Rodrigo Braz Monteiro.
This file is subject to the terms of halley_license.txt.

\*****************************************************************/

#pragma once

#include "../text/halleystring.h"
#include <memory>
#include <functional>

struct SDL_RWops;

namespace Halley {
	class ResourceDataReader {
	public:
		virtual ~ResourceDataReader() {}
		virtual int read(void* dst, size_t size) = 0;
		virtual void seek(long long pos, int whence) = 0;
		virtual size_t tell() = 0;
		virtual void close() = 0;
	};

	class ResourceData {
	public:
		ResourceData(String path);
		virtual ~ResourceData() {}

		String getPath() const { return path; }
	private:
		String path;
	};

	class ResourceDataStatic : public ResourceData {
	public:
		ResourceDataStatic(String path);
		ResourceDataStatic(void* data, size_t size, String path);

		void set(void* data, size_t size);
		bool isLoaded() const;

		void* getData();
		const void* getData() const;
		size_t getSize() const;
		String getString() const;

	private:
		std::shared_ptr<char> data;
		size_t size;
		bool loaded;
	};

	typedef std::function<std::unique_ptr<ResourceDataReader>()> ResourceDataMakeReader;
	class ResourceDataStream : public ResourceData {
	public:
		ResourceDataStream(String path, ResourceDataMakeReader makeReader);
		std::unique_ptr<ResourceDataReader> getReader() const { return std::move(make()); }

	private:
		ResourceDataMakeReader make;
	};
}