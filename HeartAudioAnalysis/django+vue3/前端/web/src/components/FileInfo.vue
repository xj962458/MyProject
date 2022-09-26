<template>
  <ul>
    <li>
      <div>文件名称</div>
      <div>{{ store.state.currentData.filename }}</div>
    </li>
    <li>
      <div>采样频率</div>
      <div>{{ store.state.currentData.sr }}</div>
    </li>
    <li>
      <div>音频时长</div>
      <div>{{ store.state.currentData.times }}</div>
    </li>
    <li>
      <div>疾病类型</div>
      <div>{{ store.state.currentData.illness }}</div>
    </li>
    <li>
      <div>采集位置</div>
      <div>{{ store.state.currentData.position }}</div>
    </li>
  </ul>
</template>

<script lang="ts" setup>
import { useStore } from "vuex";
const store = useStore();
</script>

<style>
* {
  /* 初始化 */
  margin: 0;
  padding: 0;
}

ul {
  /* 让li水平排列 */
  display: flex;
  width: 100%;
}

li {
  flex: 2;
}
ul li {
  /* 相对定位 */
  position: relative;
  list-style: none;
  width: 160px;
  height: 50px;
  /* 光标变小手 */
  cursor: pointer;
  /* 开启3D */
  transform-style: preserve-3d;
  /* 设置过渡 */
  transition: 0.5s;
}
ul li div {
  /* 绝对定位 */
  position: absolute;
  top: 0;
  left: 0;
  width: 100%;
  height: 100%;
  display: flex;
  justify-content: center;
  align-items: center;
  color: #fff;
}
/* 每个li元素里的第一个div */
ul li div:first-child {
  background-color: #8f0bed;
  transform: translateZ(25px);
}
/* 每个li元素里的最后一个div */
ul li div:last-child {
  background-color: #081fd0;
  transform: translateY(25px) rotateX(-90deg);
}
/* 鼠标移入沿X轴旋转90度 */
ul li:hover {
  transform: rotateX(90deg);
}
</style>
