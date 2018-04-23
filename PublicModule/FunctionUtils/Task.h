#pragma once

#include "Global.h"
#include <functional>
#include <utility>
#include <memory>
#include <type_traits>
#include <ctime>

namespace SSUtils
{
	namespace Function
	{
		struct Task
		{
			std::function<void()> task;
			uint32 priority;
			uint32 time;

			Task(const std::function<void()> _task, const uint32 _priority = 0, const uint32 _time = static_cast<uint32>(clock()));
			template<typename F, typename... Args>
			Task(const std::shared_ptr<std::packaged_task<typename std::result_of<F(Args...)>::type>> _task, const uint32 _priority = 0, const uint32 _time = static_cast<uint32>(clock()))
				: Task([_task]() { (*_task)(); }, _priority, _time) {};
			Task(const Task &ano) = delete;
			Task(Task &&ano) = default;
			Task &operator=(const Task &rhs) = delete;
			Task &operator=(Task &&rhs) = delete;
			~Task(void) = default;

			inline const uint32 waitMilliseconds(void) const;
		};

		inline const bool DefaultTaskCompare(const std::shared_ptr<Task> lhs, const std::shared_ptr<Task> rhs);
		using TaskCompareFunction = std::function<const bool(const std::shared_ptr<Task>, const std::shared_ptr<Task>)>;
		extern const TaskCompareFunction DefaultTaskCompareFunction;
	};
};
