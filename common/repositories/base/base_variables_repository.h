/**
 * EQEmulator: Everquest Server Emulator
 * Copyright (C) 2001-2020 EQEmulator Development Team (https://github.com/EQEmu/Server)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY except by those people which sell it, which
 * are required to give you total support for your newly bought product;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 *
 */

/**
 * This repository was automatically generated and is NOT to be modified directly.
 * Any repository modifications are meant to be made to
 * the repository extending the base. Any modifications to base repositories are to
 * be made by the generator only
 */

#ifndef EQEMU_BASE_VARIABLES_REPOSITORY_H
#define EQEMU_BASE_VARIABLES_REPOSITORY_H

#include "../../database.h"
#include "../../strings.h"

class BaseVariablesRepository {
public:
	struct Variables {
		std::string varname;
		std::string value;
		std::string information;
		std::string ts;
	};

	static std::string PrimaryKey()
	{
		return std::string("varname");
	}

	static std::vector<std::string> Columns()
	{
		return {
			"varname",
			"value",
			"information",
			"ts",
		};
	}

	static std::string ColumnsRaw()
	{
		return std::string(Strings::Implode(", ", Columns()));
	}

	static std::string InsertColumnsRaw()
	{
		std::vector<std::string> insert_columns;

		for (auto &column : Columns()) {
			if (column == PrimaryKey()) {
				continue;
			}

			insert_columns.push_back(column);
		}

		return std::string(Strings::Implode(", ", insert_columns));
	}

	static std::string TableName()
	{
		return std::string("variables");
	}

	static std::string BaseSelect()
	{
		return fmt::format(
			"SELECT {} FROM {}",
			ColumnsRaw(),
			TableName()
		);
	}

	static std::string BaseInsert()
	{
		return fmt::format(
			"INSERT INTO {} ({}) ",
			TableName(),
			InsertColumnsRaw()
		);
	}

	static Variables NewEntity()
	{
		Variables entry{};

		entry.varname     = "";
		entry.value       = "";
		entry.information = "";
		entry.ts          = current_timestamp();

		return entry;
	}

	static Variables GetVariablesEntry(
		const std::vector<Variables> &variabless,
		int variables_id
	)
	{
		for (auto &variables : variabless) {
			if (variables.varname == variables_id) {
				return variables;
			}
		}

		return NewEntity();
	}

	static Variables FindOne(
		int variables_id
	)
	{
		auto results = database.QueryDatabase(
			fmt::format(
				"{} WHERE id = {} LIMIT 1",
				BaseSelect(),
				variables_id
			)
		);

		auto row = results.begin();
		if (results.RowCount() == 1) {
			Variables entry{};

			entry.varname     = row[0] ? row[0] : "";
			entry.value       = row[1] ? row[1] : "";
			entry.information = row[2] ? row[2] : "";
			entry.ts          = row[3] ? row[3] : "";

			return entry;
		}

		return NewEntity();
	}

	static int DeleteOne(
		int variables_id
	)
	{
		auto results = database.QueryDatabase(
			fmt::format(
				"DELETE FROM {} WHERE {} = {}",
				TableName(),
				PrimaryKey(),
				variables_id
			)
		);

		return (results.Success() ? results.RowsAffected() : 0);
	}

	static int UpdateOne(
		Variables variables_entry
	)
	{
		std::vector<std::string> update_values;

		auto columns = Columns();

		update_values.push_back(columns[0] + " = '" + Strings::Escape(variables_entry.varname) + "'");
		update_values.push_back(columns[1] + " = '" + Strings::Escape(variables_entry.value) + "'");
		update_values.push_back(columns[2] + " = '" + Strings::Escape(variables_entry.information) + "'");
		update_values.push_back(columns[3] + " = '" + Strings::Escape(variables_entry.ts) + "'");

		auto results = database.QueryDatabase(
			fmt::format(
				"UPDATE {} SET {} WHERE {} = {}",
				TableName(),
				Strings::Implode(", ", update_values),
				PrimaryKey(),
				variables_entry.varname
			)
		);

		return (results.Success() ? results.RowsAffected() : 0);
	}

	static Variables InsertOne(
		Variables variables_entry
	)
	{
		std::vector<std::string> insert_values;

		insert_values.push_back("'" + Strings::Escape(variables_entry.varname) + "'");
		insert_values.push_back("'" + Strings::Escape(variables_entry.value) + "'");
		insert_values.push_back("'" + Strings::Escape(variables_entry.information) + "'");
		insert_values.push_back("'" + Strings::Escape(variables_entry.ts) + "'");

		auto results = database.QueryDatabase(
			fmt::format(
				"{} VALUES ({})",
				BaseInsert(),
				Strings::Implode(",", insert_values)
			)
		);

		if (results.Success()) {
			variables_entry.varname = results.LastInsertedID();
			return variables_entry;
		}

		variables_entry = NewEntity();

		return variables_entry;
	}

	static int InsertMany(
		std::vector<Variables> variables_entries
	)
	{
		std::vector<std::string> insert_chunks;

		for (auto &variables_entry: variables_entries) {
			std::vector<std::string> insert_values;

			insert_values.push_back("'" + Strings::Escape(variables_entry.varname) + "'");
			insert_values.push_back("'" + Strings::Escape(variables_entry.value) + "'");
			insert_values.push_back("'" + Strings::Escape(variables_entry.information) + "'");
			insert_values.push_back("'" + Strings::Escape(variables_entry.ts) + "'");

			insert_chunks.push_back("(" + Strings::Implode(",", insert_values) + ")");
		}

		std::vector<std::string> insert_values;

		auto results = database.QueryDatabase(
			fmt::format(
				"{} VALUES {}",
				BaseInsert(),
				Strings::Implode(",", insert_chunks)
			)
		);

		return (results.Success() ? results.RowsAffected() : 0);
	}

	static std::vector<Variables> All()
	{
		std::vector<Variables> all_entries;

		auto results = database.QueryDatabase(
			fmt::format(
				"{}",
				BaseSelect()
			)
		);

		all_entries.reserve(results.RowCount());

		for (auto row = results.begin(); row != results.end(); ++row) {
			Variables entry{};

			entry.varname     = row[0] ? row[0] : "";
			entry.value       = row[1] ? row[1] : "";
			entry.information = row[2] ? row[2] : "";
			entry.ts          = row[3] ? row[3] : "";

			all_entries.push_back(entry);
		}

		return all_entries;
	}

	static std::vector<Variables> GetWhere(std::string where_filter)
	{
		std::vector<Variables> all_entries;

		auto results = database.QueryDatabase(
			fmt::format(
				"{} WHERE {}",
				BaseSelect(),
				where_filter
			)
		);

		all_entries.reserve(results.RowCount());

		for (auto row = results.begin(); row != results.end(); ++row) {
			Variables entry{};

			entry.varname     = row[0] ? row[0] : "";
			entry.value       = row[1] ? row[1] : "";
			entry.information = row[2] ? row[2] : "";
			entry.ts          = row[3] ? row[3] : "";

			all_entries.push_back(entry);
		}

		return all_entries;
	}

	static int DeleteWhere(std::string where_filter)
	{
		auto results = database.QueryDatabase(
			fmt::format(
				"DELETE FROM {} WHERE {}",
				TableName(),
				PrimaryKey(),
				where_filter
			)
		);

		return (results.Success() ? results.RowsAffected() : 0);
	}

};

#endif //EQEMU_BASE_VARIABLES_REPOSITORY_H
