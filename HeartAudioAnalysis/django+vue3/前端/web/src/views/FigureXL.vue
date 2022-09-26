<template>
  <div>
    <div>
      <FileInfo></FileInfo>
    </div>
    <div>
      <XLFigure></XLFigure>
    </div>
    <div>
      <FileUpload></FileUpload>
    </div>
    <div><FileList></FileList></div>
  </div>
</template>

<script lang="ts">
import { Options, Vue } from "vue-class-component";
import XLFigure from "@/components/XLFigure.vue";
import FileInfo from "@/components/FileInfo.vue";
import FileUpload from "@/components/FileUpload.vue";
import FileList from "@/components/FileList.vue";

@Options({
  components: {
    FileInfo,
    FileUpload,
    XLFigure,
    FileList,
  },
})
export default class HomeView extends Vue {}
</script>
